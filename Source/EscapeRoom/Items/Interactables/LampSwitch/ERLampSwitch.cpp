// Fill out your copyright notice in the Description page of Project Settings.


#include "ERLampSwitch.h"


AERLampSwitch::AERLampSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchMesh->SetupAttachment(RootMesh);
	SwitchMesh->SetCollisionProfileName(TEXT("NoCollision"));

	OutlineMeshComponentPtr = SwitchMesh;
}
