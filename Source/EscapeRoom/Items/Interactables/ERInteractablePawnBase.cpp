// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractablePawnBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"


AERInteractablePawnBase::AERInteractablePawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("BlockAll"));

	InteractArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractArea"));
	InteractArea->SetupAttachment(RootMesh);
	InteractArea->SetCollisionProfileName(TEXT("InteractArea"));

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(InteractArea);
	InteractWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidget->SetDrawAtDesiredSize(true);
	// At start it's hidden
	InteractWidget->SetVisibility(false);
}

void AERInteractablePawnBase::InteractStart_Implementation(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
}

void AERInteractablePawnBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractKeyWidgetComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!OutlineMeshComponentPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|OutlineMesh is nullptr. Set it in C++, in constructor."), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidget->SetVisibility(bShowInteract);

	OutlineMeshComponentPtr->SetRenderCustomDepth(bShowInteract);
	OutlineMeshComponentPtr->SetCustomDepthStencilValue(bShowInteract ? 1 : 0);
}

void AERInteractablePawnBase::EnableInteraction() const
{
#pragma region Nullchecks
	if (!InteractArea)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractArea is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractArea->SetCollisionProfileName(TEXT("InteractArea"));
}

void AERInteractablePawnBase::DisableInteraction() const
{
#pragma region Nullchecks
	if (!InteractArea)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractArea is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractArea->SetCollisionProfileName(TEXT("NoCollision"));
}
