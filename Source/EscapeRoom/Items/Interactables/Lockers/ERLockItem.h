// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERUnlockInterface.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ERLockItem.generated.h"

/**
 * Base class for items/objects that can be locked and with possibility to unlock with keys (ERKeyItem and derivatives)
 */
// TODO Create and implement unlock interface
UCLASS()
class ESCAPEROOM_API AERLockItem : public AERInteractableActor, public IERUnlockInterface
{
	GENERATED_BODY()

public:
	AERLockItem();

	/**
	 * Overriding Unlock function from ERUnlockInterface
	 */
	virtual void Unlock_Implementation() override;

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;
	/**
	 * TODO when opening the first time locked item delay it and add sound for unlocking it with a key,
	 * but only for a key or something that you need to HAVE,
	 * because if it is unlocking with a keypad, the sound should be heard after unlocking it with a keypad not when opening
	 */
protected:
	UPROPERTY(BlueprintReadOnly, Category="ER")
	bool bLocked{true};
};
