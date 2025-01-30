// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeyComponent.h"

#include "ERLockComponent.h"
#include "Kismet/GameplayStatics.h"


UERKeyComponent::UERKeyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UERKeyComponent::BeginPlay()
{
	Super::BeginPlay();

	PopulateLockedItemsFromTags();
}

void UERKeyComponent::UnlockLockedItems()
{
	// If LockedItems array is empty, means nothing was set up
	if (LockedItems.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|%s: LockedItems array is empty, nothing to unlock"), *GetOwner()->GetName(), *FString(__FUNCTION__))
	}

	// Loop through all locked items and unlock them if can, if some doesn't have lock component return and throw Warning
	for (const AActor* LockedItem : LockedItems)
	{
#pragma region Nullchecks
		if (!LockedItem)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s|LockedItems is nullptr"), *FString(__FUNCTION__))
			return;
		}
#pragma endregion

		// Check if LockedItem has lock component
		UERLockComponent* LockComponent{Cast<UERLockComponent>(LockedItem->GetComponentByClass(UERLockComponent::StaticClass()))};
		if (LockComponent)
		{
			LockComponent->Unlock();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: does not have ERLockComponent"), *LockedItem->GetName())
			return;
		}
	}
}

void UERKeyComponent::PopulateLockedItemsFromTags()
{
	// Early return if no parent tags are set
	if (LockedParentTag.IsNone())
	{
		return;
	}

	TArray<AActor*> TaggedParents;
	UGameplayStatics::GetAllActorsWithTag(this, LockedParentTag, TaggedParents);

	if (TaggedParents.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|%s: Wrong LockedParentTag name"), *GetOwner()->GetName(), *FString(__FUNCTION__))
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
		// TODO try combine ChildActorComponent and ActorComponent initialization
		// It returns first encountered component of this type and with this tag
		UActorComponent* ActorComponent{TaggedParent->FindComponentByTag(UChildActorComponent::StaticClass(), LockedChildTag)};

		if (!ActorComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s|%s: Wrong LockedChildTag name"), *GetOwner()->GetName(), *FString(__FUNCTION__))
			return;
		}

		const UChildActorComponent* ChildActorComponent{Cast<UChildActorComponent>(ActorComponent)};

		LockedItems.Add(ChildActorComponent->GetChildActor());
	}
}
