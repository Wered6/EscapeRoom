// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableActorBase.h"
#include "Components/WidgetComponent.h"
#include "EscapeRoom/UI/ERInteractIconWidget.h"


AERInteractableActorBase::AERInteractableActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERInteractableActorBase::BeginPlay()
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

	InteractWidget->Init(InteractCategory, InteractType, InitialRoundProgressbarPercent, RoundProgressbarSize, IconSize);
	InteractWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidgetComp->SetDrawAtDesiredSize(true);
	InteractWidgetComp->SetVisibility(false);
	InteractWidgetComp->SetWidget(InteractWidget);
	InteractWidgetComp->RegisterComponent();

	USceneComponent* WidgetAttachComp{Execute_GetWidgetAttachmentComponent(this)};
	if (!WidgetAttachComp)
	{
		WidgetAttachComp = GetRootComponent();
	}
	InteractWidgetComp->AttachToComponent(WidgetAttachComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void AERInteractableActorBase::SetCanInteract(const bool bNewCanInteract)
{
	bCanInteract = bNewCanInteract;
}

void AERInteractableActorBase::SetShowInteractWidget(const bool bShow) const
{
#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidgetComp->SetVisibility(bShow);
}

void AERInteractableActorBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidgetComp->SetVisibility(bShowInteract);

	if (OutlineMeshComponentPtr)
	{
		OutlineMeshComponentPtr->SetRenderCustomDepth(bShowInteract);
		OutlineMeshComponentPtr->SetCustomDepthStencilValue(bShowInteract ? 1 : 0);
	}
}

void AERInteractableActorBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
	UE_LOG(LogTemp, Warning, TEXT("PressStarted"))
}

void AERInteractableActorBase::InteractPressTriggered_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("PressTriggered"))
}

void AERInteractableActorBase::InteractPressCompleted_Implementation()
{
	InteractInstigator = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("PressCompleted"))
}

void AERInteractableActorBase::InteractHoldStarted_Implementation(AActor* OtherInstigator, float& OutHoldTimeThreshold)
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

void AERInteractableActorBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float CurrentRoundProgressbarPercent{FMath::Clamp(ElapsedSeconds / HoldTimeThreshold, 0.f, 1.f)};
	InteractWidget->SetProgressbarPercent(CurrentRoundProgressbarPercent);
	UE_LOG(LogTemp, Warning, TEXT("HoldOngoing"))
}

void AERInteractableActorBase::InteractHoldTriggered_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("HoldTriggered"))
}

void AERInteractableActorBase::InteractHoldCanceled_Implementation()
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

void AERInteractableActorBase::InteractHoldCompleted_Implementation()
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

bool AERInteractableActorBase::DoesUseCustomInteractArea_Implementation()
{
	return bUseCustomInteractArea;
}

bool AERInteractableActorBase::CanInteract_Implementation()
{
	return bCanInteract;
}

EERInteractType AERInteractableActorBase::GetInteractType_Implementation()
{
	return InteractType;
}
