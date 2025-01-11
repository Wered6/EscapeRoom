// Fill out your copyright notice in the Description page of Project Settings.


#include "ERDoor.h"


AERDoor::AERDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh->SetCollisionResponseToAllChannels(ECR_Block);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootMesh);
	DoorMesh->SetCollisionResponseToAllChannels(ECR_Block);
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}
