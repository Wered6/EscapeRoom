// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "EscapeRoom/Flashlight/Flashlight.h"
#include "EscapeRoom/Interact/ERInteractInterface.h"
#include "EscapeRoom/PlayerController/ERPlayerController.h"

AERCharacter::AERCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	// Create CameraComponent
	Camera1P = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1P"));
	Camera1P->SetupAttachment(GetCapsuleComponent());
	Camera1P->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	Camera1P->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(Camera1P);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-4.f, 0.f, -150.f));
}

void AERCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// TODO try to capture PlayerController here and save it in class instead of functions

	if (!Controller)
	{
		return;
	}

#pragma region Nullchecks
	if (!DefaultMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DefaultMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Add input Mapping Context
	const APlayerController* PlayerController{Cast<APlayerController>(Controller)};

#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())};

#pragma region Nullchecks
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Subsystem is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AERCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PerformInteractionCheck();
}

void AERCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
#pragma region Nullchecks
	if (!MoveAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|MoveAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LookAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LookAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!FlashlightAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!InteractAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(PlayerInputComponent)};

#pragma region Nullchecks
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnhancedInputComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AERCharacter::Move);

	// Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AERCharacter::Look);

	// Flashlight
	EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AERCharacter::FlashlightButtonPressed);

	// Interact
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AERCharacter::Interact);
}

void AERCharacter::Move(const FInputActionValue& Value)
{
#pragma region Nullchecks
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Controller is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Input is a Vector2D
	const FVector2D MovementVector{Value.Get<FVector2D>()};

	// Add movement
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AERCharacter::Look(const FInputActionValue& Value)
{
#pragma region Nullchecks
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Controller is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Input is a Vector2D
	const FVector2D LookAxisVector{Value.Get<FVector2D>()};

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::FlashlightButtonPressed()
{
	if (!EquippedFlashlight)
	{
		return;
	}

	EquippedFlashlight->SwitchToNextColor();
	const AERPlayerController* PC{Cast<AERPlayerController>(GetController())};

#pragma region Nullchecks
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PC is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	PC->OutlineUltraVioletColor(EquippedFlashlight->GetCurrentColor());
}

void AERCharacter::Interact()
{
	// Return if no interactable actor found
	if (!InteractableActor)
	{
		return;
	}

	// If interactable actor has interact interface fire interact start function
	if (InteractableActor->Implements<UERInteractInterface>())
	{
		IERInteractInterface::Execute_InteractStart(InteractableActor, this);
	}
}

void AERCharacter::PerformInteractionCheck()
{
	// Get the player controller
	const APlayerController* PC{Cast<APlayerController>(GetController())};

#pragma region Nullchecks
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PC is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Get camera location and direction
	FVector CameraLocation;
	FRotator CameraRotation;
	PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Define the start and end points of the line trace
	const FVector Start{CameraLocation};
	const FVector End{Start + CameraRotation.Vector() * InteractionDistance};

	// Perform the line trace
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility
	);

	// Check if the hit actor implements the interact interface
	if (HitResult.GetActor())
	{
		AActor* HitActor{HitResult.GetActor()};
		// If hit actor same as interactable actor early return
		if (HitActor == InteractableActor)
		{
			return;
		}
		// Else if interactable actor is already set and we aren't pointing at him, hide interaction UI of current interactable actor
		// No check for implement because we can always interact with interactable actor
		if (InteractableActor)
		{
			IERInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
		}

		// If HitActor implements interact interface show interaction UI
		if (HitActor->Implements<UERInteractInterface>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit interactable actor: %s"), *HitActor->GetName())
			IERInteractInterface::Execute_DisplayInteractionUI(HitActor, true);
			InteractableActor = HitActor;
		}
		// Else set InteractableActor to nullptr
		else
		{
			InteractableActor = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Hit object doesn't implement interact interface"))
		}
	}
	// If we hit nothing, hide interaction UI of current interactable actor
	// No check for implement because we can always interact with interactable actor
	else if (InteractableActor)
	{
		IERInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
		InteractableActor = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("No object hit"))
	}
}

void AERCharacter::EquipFlashlight(AFlashlight* Flashlight)
{
	EquippedFlashlight = Flashlight;
	const AERPlayerController* PC{Cast<AERPlayerController>(GetController())};

#pragma region Nullchecks
	if (!EquippedFlashlight)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EquippedFlashlight is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PC is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	EquippedFlashlight->SetOwner(this);
	PC->AddToViewportFlashlightWidget();

	const USkeletalMeshSocket* HandSocket{Mesh1P->GetSocketByName(FName("RightHandSocket"))};

#pragma region Nullchecks
	if (!HandSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|HandSocket is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	HandSocket->AttachActor(EquippedFlashlight, Mesh1P);
}
