// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinetDoor.h"
#include "EscapeRoom/Components/ERLockComponent.h"


AERCabinetDoor::AERCabinetDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));
	SetRootComponent(DoorMesh);

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));
}
