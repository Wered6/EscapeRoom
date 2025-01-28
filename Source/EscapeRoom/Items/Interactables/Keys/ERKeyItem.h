// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ERKeyItem.generated.h"

class AERLockedItem;

/**
 * Base class for items/objects than can unlock locked items (ERLockItem and derivatives)
 */
UCLASS()
class ESCAPEROOM_API AERKeyItem : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERKeyItem();

protected:
	virtual void BeginPlay() override;

	/**
	 * Unlocking all locked items in LockedItems array
	 */
	void UnlockLockedItems();

private:
	void PopulateLockedItemsFromTags();

	/**
	 * Use for simple "many keys-one door".
	 * Tags can override LockedItem
	 */
	UPROPERTY(EditInstanceOnly, Category="ER|Unlock")
	TArray<AActor*> LockedItems;
	/**
	 * Use for complex "many keys-many doors" or actor with children like Cabinet.
	 * If LockedChildTag is empty, it will search only through LockedParentTag
	 */
	UPROPERTY(EditAnywhere, Category="ER|Unlock")
	FName LockedParentTag{};
	/**
	 * If LockedParentTag is empty, but LockedChildTag is not empty it won't use tags anyway.
	 */
	UPROPERTY(EditAnywhere, Category="ER|Unlock")
	FName LockedChildTag{};
	/**
	 * TODO think of creating in interactable actor (or some child class) more items to interact with
	 * just like here, soi for example in LampSwitch we can pick multiple lamps
	 */
};
