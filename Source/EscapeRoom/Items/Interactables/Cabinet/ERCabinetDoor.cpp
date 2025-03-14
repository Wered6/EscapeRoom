// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinetDoor.h"
#include "EscapeRoom/Components/ERInteractableComponent.h"
#include "EscapeRoom/Components/ERLockComponent.h"


AERCabinetDoor::AERCabinetDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));

	InteractableComponent = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(DoorMesh);
}
