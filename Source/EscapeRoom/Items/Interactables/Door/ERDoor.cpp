// Fill out your copyright notice in the Description page of Project Settings.


#include "ERDoor.h"

#include "Components/BoxComponent.h"
#include "EscapeRoom/Components/ERLockComponent.h"


AERDoor::AERDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootMesh);
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));

	InteractArea->SetupAttachment(DoorMesh);

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	HandleMesh->SetupAttachment(DoorMesh);
	HandleMesh->SetCollisionProfileName(TEXT("NoCollision"));

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));

	OutlineMeshComponentPtr = HandleMesh;
}
