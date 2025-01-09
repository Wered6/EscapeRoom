// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableActor.h"
#include "Components/WidgetComponent.h"


AERInteractableActor::AERInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractKeyWidget"));
	InteractWidget->SetupAttachment(RootMesh);
	InteractWidget->SetWidgetSpace(EWidgetSpace::Screen);
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
#pragma endregion

	InteractWidget->SetVisibility(bShowInteract);
}
