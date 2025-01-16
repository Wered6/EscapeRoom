// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKey.h"
#include "EscapeRoom/Items/Interactables/Lockers/ERLockItem.h"


AERKey::AERKey()
{
	PrimaryActorTick.bCanEverTick = false;

	OutlineMeshComponentPtr = RootMesh;
}

void AERKey::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	// If LocketItems array is empty, means nothing was set up
	if (LockedItems.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: LockedItems array is empty, can't pick it up"), *this->GetName())
		return;
	}

	// Loop through all locked items and unlock them if can, if some doesn't have unlock interface return and throw Warning
	for (AActor* Item : LockedItems)
	{
#pragma region Nullchecks
		if (!Item)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s|Item is nullptr"), *FString(__FUNCTION__))
			return;
		}
#pragma endregion

		if (Item->Implements<UERUnlockInterface>())
		{
			IERUnlockInterface::Execute_Unlock(Item);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s does not implement UnlockInterface"), *Item->GetName())
			return;
		}
	}

	Destroy();
}
