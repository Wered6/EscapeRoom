// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableActor.h"
#include "Components/WidgetComponent.h"


AERInteractableActor::AERInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractKeyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractKeyWidgetComponent"));
	InteractKeyWidget->SetupAttachment(RootComponent);
	InteractKeyWidget->SetWidgetSpace(EWidgetSpace::Screen);
	// At start it's hidden because we want to see it only when player is near enough
	InteractKeyWidget->SetVisibility(false);
}

void AERInteractableActor::InteractStart_Implementation(AActor* OtherInstigator)
{
	InteractInstigator = OtherInstigator;
	// TODO highlight outline around object and show widget to interact (preferably E key)
}

void AERInteractableActor::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
#pragma region Nullchecks
	if (!InteractKeyWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractKeyWidgetComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractKeyWidget->SetVisibility(bShowInteract);
}
