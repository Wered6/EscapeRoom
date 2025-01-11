// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKey.h"
#include "EscapeRoom/Items/Interactables/Lockers/ERLockItem.h"


AERKey::AERKey()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKey::InteractStart_Implementation(AActor* OtherInstigator)
{
#pragma region Nullchecks
	if (!LockedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LockedItem is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Super::InteractStart_Implementation(OtherInstigator);

	LockedItem->Unlock();

	Destroy();
}
