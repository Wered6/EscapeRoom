// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPicture.h"
#include "EscapeRoom/Components/ERInteractableComponent.h"


AERPicture::AERPicture()
{
	PrimaryActorTick.bCanEverTick = false;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontMesh"));
	SetRootComponent(FrameMesh);
	FrameMesh->SetCollisionProfileName(TEXT("NoCollision"));
	PaintingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaintingMesh"));
	PaintingMesh->SetupAttachment(FrameMesh);
	PaintingMesh->SetCollisionProfileName(TEXT("NoCollision"));
	BackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackMesh"));
	BackMesh->SetupAttachment(FrameMesh);
	BackMesh->SetCollisionProfileName(TEXT("NoCollision"));

	InteractableComponent = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(FrameMesh);
}
