// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"
#include "GameFramework/Character.h"


UERInteractComponent::UERInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UERInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO consider do it in PostLoad
	CharacterOwner = Cast<ACharacter>(GetOwner());

#pragma region Nullchecks
	if (!CharacterOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|CharacterOwner is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!InteractMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const APlayerController* PlayerController{CharacterOwner->GetController<APlayerController>()};

#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())};
	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(PlayerController->InputComponent)};

#pragma region Nullchecks
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Subsystem is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnhancedInputComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Subsystem->AddMappingContext(InteractMappingContext, 0);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UERInteractComponent::Interact);
}

void UERInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformInteractionCheck();
}

// TODO try const function
void UERInteractComponent::Interact()
{
#pragma region Nullchecks
	if (!CharacterOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|CharacterOwner is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	if (!InteractableActor)
	{
		return;
	}

	if (InteractableActor->Implements<UERInteractInterface>())
	{
		IERInteractInterface::Execute_InteractStart(InteractableActor, CharacterOwner);
	}
}

void UERInteractComponent::PerformInteractionCheck()
{
	if (!bCanCheckInteraction)
	{
		return;
	}

#pragma region Nullchecks
	if (!CharacterOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|CharacterOwner is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const APlayerController* PlayerController{CharacterOwner->GetController<APlayerController>()};

#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Get camera location and direction
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Define the start and end points of the line trace
	const FVector Start{CameraLocation};
	const FVector End{Start + CameraRotation.Vector() * InteractionDistance};

	// Perform the line trace
	FHitResult HitResult;
	const bool bHit
	{
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility)
	};

	// If nothing was hit, reset interaction and return
	if (!bHit)
	{
		ClearInteraction();
		return;
	}

	AActor* HitActor{HitResult.GetActor()};
	UPrimitiveComponent* HitComponent{HitResult.GetComponent()};

	// If hitting the same interactable component, do nothing and return
	if (HitComponent == InteractableHitComponent)
	{
		return;
	}

	// If previously interacting with something else, hide its UI
	if (InteractableActor)
	{
		IERInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
	}

	// Check if the hit actor implements the interact interface and has correct collision
	if (HitActor->Implements<UERInteractInterface>() && HitComponent->GetCollisionProfileName() == FName("InteractArea"))
	{
		IERInteractInterface::Execute_DisplayInteractionUI(HitActor, true);
		InteractableActor = HitActor;
		InteractableHitComponent = HitComponent;
	}
	else
	{
		ClearInteraction();
	}
}

void UERInteractComponent::ClearInteraction()
{
	if (InteractableActor)
	{
		IERInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
	}
	InteractableActor = nullptr;
	InteractableHitComponent = nullptr;
}
