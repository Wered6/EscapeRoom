// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPicture.h"


AERPicture::AERPicture()
{
	PrimaryActorTick.bCanEverTick = false;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontMesh"));
	FrameMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(FrameMesh);

	PaintingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaintingMesh"));
	PaintingMesh->SetCollisionProfileName(TEXT("NoCollision"));
	PaintingMesh->SetupAttachment(FrameMesh);

	BackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackMesh"));
	BackMesh->SetCollisionProfileName(TEXT("NoCollision"));
	BackMesh->SetupAttachment(FrameMesh);
}
