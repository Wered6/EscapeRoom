// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableComponent.h"
#include "ERInteractableActorBase.h"
#include "ERInteractableCharacterBase.h"
#include "ERInteractablePawnBase.h"
#include "ERInteractIconWidget.h"
#include "ERInteractInterface.h"
#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInteractableComponent, Log, All);


UERInteractableComponent::UERInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UERInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeInteractWidget();
	UpdateWidgetAttachment();
}

void UERInteractableComponent::AddOutlineMeshComponent(UMeshComponent* MeshComponent)
{
	OutlineMeshComps.Add(MeshComponent);
}

void UERInteractableComponent::SetOutlineMeshComponents(const TArray<UMeshComponent*>& NewOutlineMeshComponents)
{
	OutlineMeshComps = NewOutlineMeshComponents;
}

void UERInteractableComponent::DisplayInteractionUI(const bool bShowInteract)
{
#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidgetComp->SetVisibility(bShowInteract);

	for (UMeshComponent* OutlineMeshComponent : OutlineMeshComps)
	{
		if (OutlineMeshComponent)
		{
			OutlineMeshComponent->SetRenderCustomDepth(bShowInteract);
			OutlineMeshComponent->SetCustomDepthStencilValue(bShowInteract ? 1 : 0);
		}
	}
}

void UERInteractableComponent::InteractPressStarted(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
	UE_LOG(LogTemp, Warning, TEXT("PressStarted"))
}

void UERInteractableComponent::InteractPressTriggered()
{
	UE_LOG(LogTemp, Warning, TEXT("PressTriggered"))
}

void UERInteractableComponent::InteractPressCompleted()
{
	InteractInstigator = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("PressCompleted"))
}

float UERInteractableComponent::InteractHoldStarted(AActor* OtherInstigator)
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return 0.f;
	}
#pragma endregion

	InteractInstigator = OtherInstigator;
	InteractWidget->SetIsHolding(true);
	UE_LOG(LogTemp, Warning, TEXT("HoldStarted"))

	return HoldTimeThreshold;
}

void UERInteractableComponent::InteractHoldOngoing(const float ElapsedSeconds)
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float ProgressFraction{FMath::Clamp(ElapsedSeconds / HoldTimeThreshold, 0.f, 1.f)};
	InteractWidget->SetIconOpacity(ProgressFraction);
	InteractWidget->SetProgressCircleOpacity(ProgressFraction);
	InteractWidget->SetProgressCirclePercent(ProgressFraction);
	UE_LOG(LogTemp, Warning, TEXT("HoldOngoing"))
}

void UERInteractableComponent::InteractHoldTriggered()
{
	UE_LOG(LogTemp, Warning, TEXT("HoldTriggered"))
}

void UERInteractableComponent::InteractHoldCanceled()
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractInstigator = nullptr;
	InteractWidget->SetIsHolding(false);
	UE_LOG(LogTemp, Warning, TEXT("HoldCanceled"))
}

void UERInteractableComponent::InteractHoldCompleted()
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractInstigator = nullptr;
	InteractWidget->SetIsHolding(false);
	UE_LOG(LogTemp, Warning, TEXT("HoldCompleted"))
}

bool UERInteractableComponent::DoesUseCustomInteractArea() const
{
	return bUseCustomInteractArea;
}

void UERInteractableComponent::SetCanInteract(const bool bNewCanInteract)
{
	bCanInteract = bNewCanInteract;
}

bool UERInteractableComponent::GetCanInteract() const
{
	return bCanInteract;
}

EERInteractType UERInteractableComponent::GetInteractType() const
{
	return InteractType;
}

void UERInteractableComponent::OnRegister()
{
	Super::OnRegister();

	AActor* Owner{GetOwner()};
	if (!Cast<AERInteractableActorBase>(Owner) && !Cast<AERInteractablePawnBase>(Owner) && !Cast<AERInteractableCharacterBase>(Owner))
	{
		UE_LOG(LogInteractableComponent, Error, TEXT("%s owned by %s must register a component owned by a InteractableActorBase, InteractablePawnBase or InteractableCharacterBase"), *GetName(), *GetNameSafe(GetOwner()))
	}
}

void UERInteractableComponent::InitializeInteractWidget()
{
#pragma region Nullchecks
	if (!InteractWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetClass is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidget = CreateWidget<UERInteractIconWidget>(GetWorld(), InteractWidgetClass);
	InteractWidgetComp = NewObject<UWidgetComponent>(this, TEXT("InteractWidgetComp"));

#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidget->Init(InteractCategory,
	                     InteractType,
	                     MinimalIconOpacity,
	                     IconSize,
	                     MinimalProgressCircleOpacity,
	                     ProgressCircleSize);
	InteractWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidgetComp->SetDrawAtDesiredSize(true);
	InteractWidgetComp->SetVisibility(false);
	InteractWidgetComp->SetWidget(InteractWidget);
	InteractWidgetComp->RegisterComponent();
}

void UERInteractableComponent::UpdateWidgetAttachment() const
{
#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	USceneComponent* WidgetAttachComp{IERInteractInterface::Execute_GetWidgetAttachmentComponent(GetOwner())};
	if (!WidgetAttachComp)
	{
		WidgetAttachComp = GetOwner()->GetRootComponent();
	}
	InteractWidgetComp->AttachToComponent(WidgetAttachComp, FAttachmentTransformRules::KeepRelativeTransform);
}
