// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ERKeyItem.generated.h"

class AERLockItem;

/**
 * Base class for items/objects than can unlock locked items (ERLockItem and derivatives)
 */
UCLASS()
class ESCAPEROOM_API AERKeyItem : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERKeyItem();

	// TODO Check if it's necessary here
	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

protected:
	/**
	 * Use for simple "many keys-one door".
	 * Tags can override LockedItem
	 */
	UPROPERTY(EditInstanceOnly, Category="ER|Actors to unlock")
	TArray<AActor*> LockedItems;

	/**
	 * Use for complex "many keys-many doors" or actor with children like Cabinet.
	 * If LockedChildTag is empty, it will search only through LockedParentTag
	 */
	UPROPERTY(EditAnywhere, Category="ER|Actors to unlock")
	FName LockedParentTag{};
	/**
	 * If LockedParentTag is empty, but LockedChildTag is not empty it won't use tags anyway.
	 */
	UPROPERTY(EditAnywhere, Category="ER|Actors to unlock")
	FName LockedChildTag{};
};
