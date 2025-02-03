// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"


AERInteractableActor::AERInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("BlockAll"));

	InteractArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractArea"));
	InteractArea->SetupAttachment(RootMesh);
	InteractArea->SetCollisionProfileName(TEXT("InteractArea"));

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractKeyWidget"));
	InteractWidget->SetupAttachment(InteractArea);
	InteractWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidget->SetDrawAtDesiredSize(true);
	// At start it's hidden because we want to see it only when player is near enough
	InteractWidget->SetVisibility(false);
}

void AERInteractableActor::InteractStart_Implementation(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
}

void AERInteractableActor::DisplayInteractionUI_Implementation(const bool bShowInteract)
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
	OutlineMeshComponentPtr->SetCustomDepthStencilValue(bShowInteract);
}

void AERInteractableActor::DisableInteraction() const
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
