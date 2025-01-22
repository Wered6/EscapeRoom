// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeyItem.h"
#include "EscapeRoom/Items/Interactables/Lockers/ERUnlockInterface.h"
#include "Kismet/GameplayStatics.h"

AERKeyItem::AERKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKeyItem::BeginPlay()
{
	Super::BeginPlay();

	PopulateLockedItemsFromTags();
}

void AERKeyItem::UnlockLockedItems()
{
	// If LocketItems array is empty, means nothing was set up
	if (LockedItems.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: LockedItems array is empty, nothing to unlock"), *this->GetName())
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
}

void AERKeyItem::PopulateLockedItemsFromTags()
{
	if (LockedParentTag.IsNone())
	{
		return;
	}

	TArray<AActor*> TaggedParents;
	UGameplayStatics::GetAllActorsWithTag(this, LockedParentTag, TaggedParents);

	if (TaggedParents.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Wrong LockedParentTag name"), *this->GetName())
		return;
	}

	// If no children, tagged parents array is locked items array
	if (LockedChildTag.IsNone())
	{
		LockedItems = TaggedParents;
		return;
	}

	for (const AActor* TaggedParent : TaggedParents)
	{
		UActorComponent* ActorComponent{TaggedParent->FindComponentByTag(UChildActorComponent::StaticClass(), LockedChildTag)};

		if (!ActorComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: Wrong LockedChildTag name"), *this->GetName())
			return;
		}

		const UChildActorComponent* ChildActorComponent{Cast<UChildActorComponent>(ActorComponent)};

#pragma region Nullchecks
		if (!ChildActorComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s|ChildActorComponent is nullptr"), *FString(__FUNCTION__))
			return;
		}
#pragma endregion

		LockedItems.Add(ChildActorComponent->GetChildActor());
	}
}
