// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeyItem.h"
#include "EscapeRoom/Lockers/ERLockItem.h"

AERKeyItem::AERKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKeyItem::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

#pragma region Nullchecks
	if (!LockedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LockedItem is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// If locked item has unlock interface fire unlock function
	if (LockedItem->Implements<UERUnlockInterface>())
	{
		IERUnlockInterface::Execute_Unlock(this);
	}
}
