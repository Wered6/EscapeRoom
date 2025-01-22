// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKey.h"


AERKey::AERKey()
{
	PrimaryActorTick.bCanEverTick = false;

	OutlineMeshComponentPtr = RootMesh;
}

void AERKey::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	UnlockLockedItems();
	Destroy();
}
