// Fill out your copyright notice in the Description page of Project Settings.


#include "ERLampSwitch.h"
#include "EscapeRoom/InteractionSystem/ERInteractableComponent.h"


AERLampSwitch::AERLampSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(FrameMesh);

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SwitchMesh->SetupAttachment(FrameMesh);
}

void AERLampSwitch::BeginPlay()
{
	Super::BeginPlay();

	InteractableComp->AddOutlineMeshComponent(FrameMesh);
}
