// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinet.h"


AERCabinet::AERCabinet()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	BodyMesh->SetCollisionProfileName(TEXT("BlockAll"));
	SetRootComponent(BodyMesh);

	DoorLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(BodyMesh);

	DoorRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(BodyMesh);

	DrawerFirst = CreateDefaultSubobject<UChildActorComponent>(TEXT("DrawerFirst"));
	DrawerFirst->SetupAttachment(BodyMesh);

	DrawerSecond = CreateDefaultSubobject<UChildActorComponent>(TEXT("DrawerSecond"));
	DrawerSecond->SetupAttachment(BodyMesh);

	DrawerThird = CreateDefaultSubobject<UChildActorComponent>(TEXT("DrawerThird"));
	DrawerThird->SetupAttachment(BodyMesh);
}
