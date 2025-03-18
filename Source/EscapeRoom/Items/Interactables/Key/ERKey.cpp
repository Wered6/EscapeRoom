// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKey.h"
#include "EscapeRoom/Components/ERKeyComponent.h"
#include "EscapeRoom/InteractionSystem/ERInteractableComponent.h"


AERKey::AERKey()
{
	PrimaryActorTick.bCanEverTick = false;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(KeyMesh);

	KeyComponent = CreateDefaultSubobject<UERKeyComponent>(TEXT("KeyComponent"));
}

void AERKey::BeginPlay()
{
	Super::BeginPlay();

	InteractableComp->AddOutlineMeshComponent(KeyMesh);
}

void AERKey::InteractHoldTriggered_Implementation()
{
	Super::InteractHoldTriggered_Implementation();

	KeyComponent->UnlockLockedItems();
}

void AERKey::InteractHoldCompleted_Implementation()
{
	Super::InteractHoldCompleted_Implementation();

	Destroy();
}
