// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableComponent.h"
#include "ERInteractIconWidget.h"
#include "ERInteractInterface.h"
#include "Components/WidgetComponent.h"


UERInteractableComponent::UERInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UERInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

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
	                     InitialIconOpacity,
	                     IconSize,
	                     MinimalProgressCircleOpacity,
	                     InitialProgressCircleOpacity,
	                     ProgressCircleSize,
	                     InitialProgressCirclePercent);
	InteractWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidgetComp->SetDrawAtDesiredSize(true);
	InteractWidgetComp->SetVisibility(false);
	InteractWidgetComp->SetWidget(InteractWidget);
	InteractWidgetComp->RegisterComponent();

	USceneComponent* WidgetAttachComp{IERInteractInterface::Execute_GetWidgetAttachmentComponent(GetOwner())};
	if (!WidgetAttachComp)
	{
		WidgetAttachComp = GetOwner()->GetRootComponent();
	}
	InteractWidgetComp->AttachToComponent(WidgetAttachComp, FAttachmentTransformRules::KeepRelativeTransform);
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

void UERInteractableComponent::InteractHoldStarted(AActor* OtherInstigator, float& OutHoldTimeThreshold)
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractInstigator = OtherInstigator;
	OutHoldTimeThreshold = HoldTimeThreshold;
	InteractWidget->SetIsHolding(true);
	UE_LOG(LogTemp, Warning, TEXT("HoldStarted"))
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

	const float CurrentProgressCirclePercent{FMath::Clamp(ElapsedSeconds / HoldTimeThreshold, 0.f, 1.f)};
	InteractWidget->SetProgressCircleOpacity(CurrentProgressCirclePercent);
	InteractWidget->SetProgressCirclePercent(CurrentProgressCirclePercent);
	InteractWidget->SetIconOpacity(CurrentProgressCirclePercent);
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
