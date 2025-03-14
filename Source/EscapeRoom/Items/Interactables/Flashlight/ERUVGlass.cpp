// Fill out your copyright notice in the Description page of Project Settings.


#include "ERUVGlass.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "EscapeRoom/Components/ERInteractableComponent.h"


AERUVGlass::AERUVGlass()
{
	PrimaryActorTick.bCanEverTick = false;

	GlassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlassMesh"));
	SetRootComponent(GlassMesh);
	GlassMesh->SetCollisionProfileName(TEXT("NoCollision"));

	InteractableComponent = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(GlassMesh);
}

void AERUVGlass::InteractHoldTriggered_Implementation()
{
	AERCharacter* Character{Cast<AERCharacter>(InteractableComponent->GetInteractInstigator())};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Character->CollectUVGlassData(Data);
}

void AERUVGlass::InteractHoldCompleted_Implementation()
{
	Destroy();
}
