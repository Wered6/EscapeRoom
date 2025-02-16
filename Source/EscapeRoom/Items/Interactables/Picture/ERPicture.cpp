// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPicture.h"
#include "Components/BoxComponent.h"


AERPicture::AERPicture()
{
	PrimaryActorTick.bCanEverTick = false;

	PaintingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaintingMesh"));
	PaintingMesh->SetupAttachment(RootMesh);
	PaintingMesh->SetCollisionProfileName(TEXT("NoCollision"));
	BackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackMesh"));
	BackMesh->SetupAttachment(RootMesh);
	BackMesh->SetCollisionProfileName(TEXT("NoCollision"));

	InteractArea->SetupAttachment(PaintingMesh);

	OutlineMeshComponentPtr = PaintingMesh;
}
