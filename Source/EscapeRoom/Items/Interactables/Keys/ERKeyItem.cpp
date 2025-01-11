// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeyItem.h"
#include "EscapeRoom/Items/Interactables/Lockers/ERLockItem.h"

class UERUnlockInterface;

AERKeyItem::AERKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKeyItem::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);
}
