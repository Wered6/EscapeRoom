// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKey.h"
#include "EscapeRoom/Components/ERKeyComponent.h"


AERKey::AERKey()
{
	PrimaryActorTick.bCanEverTick = false;

	KeyComponent = CreateDefaultSubobject<UERKeyComponent>(TEXT("KeyComponent"));

	OutlineMeshComponentPtr = RootMesh;
}

void AERKey::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	KeyComponent->UnlockLockedItems();
	Destroy();
}
