// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractablePawnBase.h"
#include "Components/WidgetComponent.h"
#include "EscapeRoom/UI/ERInteractIconWidget.h"


AERInteractablePawnBase::AERInteractablePawnBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERInteractablePawnBase::BeginPlay()
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

	// InteractWidget->Init(InteractCategory, InteractType, InitialRoundProgressbarPercent, RoundProgressbarSize, IconSize);
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

void AERInteractablePawnBase::SetCanInteract(const bool bNewCanInteract)
{
	bCanInteract = bNewCanInteract;
}

void AERInteractablePawnBase::SetShowInteractWidget(const bool bShow) const
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

void AERInteractablePawnBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidgetComp->SetVisibility(bShowInteract);

	for (UMeshComponent* OutlineMeshComponent : OutlineMeshComponents)
	{
		if (OutlineMeshComponent)
		{
			OutlineMeshComponent->SetRenderCustomDepth(bShowInteract);
			OutlineMeshComponent->SetCustomDepthStencilValue(bShowInteract ? 1 : 0);
		}
	}
}

void AERInteractablePawnBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
	UE_LOG(LogTemp, Warning, TEXT("PressStarted"))
}

void AERInteractablePawnBase::InteractPressTriggered_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("PressTriggered"))
}

void AERInteractablePawnBase::InteractPressCompleted_Implementation()
{
	InteractInstigator = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("PressCompleted"))
}

void AERInteractablePawnBase::InteractHoldStarted_Implementation(AActor* OtherInstigator, float& OutHoldTimeThreshold)
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

void AERInteractablePawnBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float CurrentRoundProgressbarPercent{FMath::Clamp(ElapsedSeconds / HoldTimeThreshold, 0.f, 1.f)};
	InteractWidget->SetProgressCircleOpacity(CurrentRoundProgressbarPercent);
	InteractWidget->SetProgressCirclePercent(CurrentRoundProgressbarPercent);
	UE_LOG(LogTemp, Warning, TEXT("HoldOngoing"))
}

void AERInteractablePawnBase::InteractHoldTriggered_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("HoldTriggered"))
}

void AERInteractablePawnBase::InteractHoldCanceled_Implementation()
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

void AERInteractablePawnBase::InteractHoldCompleted_Implementation()
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

bool AERInteractablePawnBase::DoesUseCustomInteractArea_Implementation()
{
	return bUseCustomInteractArea;
}

bool AERInteractablePawnBase::CanInteract_Implementation()
{
	return bCanInteract;
}

EERInteractType AERInteractablePawnBase::GetInteractType_Implementation()
{
	return InteractType;
}
