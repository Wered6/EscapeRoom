// Fill out your copyright notice in the Description page of Project Settings.


#include "ERDoor.h"


AERDoor::AERDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootMesh);
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	HandleMesh->SetupAttachment(DoorMesh);
	HandleMesh->SetCollisionProfileName(TEXT("NoCollision"));

	OutlineMeshComponentPtr = HandleMesh;
}
