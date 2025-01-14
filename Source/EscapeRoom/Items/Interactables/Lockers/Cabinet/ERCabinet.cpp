// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinet.h"


AERCabinet::AERCabinet()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("BlockAll"));
	RootMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

	DoorLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(RootMesh);
	DoorRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(RootMesh);
	DrawerFirst = CreateDefaultSubobject<UChildActorComponent>(TEXT("DrawerFirst"));
	DrawerFirst->SetupAttachment(RootMesh);
	DrawerSecond = CreateDefaultSubobject<UChildActorComponent>(TEXT("DrawerSecond"));
	DrawerSecond->SetupAttachment(RootMesh);
	DrawerThird = CreateDefaultSubobject<UChildActorComponent>(TEXT("DrawerThird"));
	DrawerThird->SetupAttachment(RootMesh);
}
