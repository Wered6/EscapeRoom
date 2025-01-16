// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeyItem.h"
#include "EscapeRoom/Items/Interactables/Lockers/ERLockItem.h"
#include "Kismet/GameplayStatics.h"

AERKeyItem::AERKeyItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKeyItem::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

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
