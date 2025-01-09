// Fill out your copyright notice in the Description page of Project Settings.


#include "ERLockItem.h"

AERLockItem::AERLockItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERLockItem::Unlock_Implementation()
{
	if (!bLocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is already unlocked"), *GetName())
	}
	UE_LOG(LogTemp, Warning, TEXT("Attempt to unlock object instance - %s"), *GetName())
}

void AERLockItem::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	if (bLocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't open %s it's locked"), *GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hurray! %s is not locked, let's open it!"), *GetName())
	}
}
