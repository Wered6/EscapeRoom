// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "EscapeRoom/Items/Interactables/Keys/ERUnlockInterface.h"
#include "GameFramework/Actor.h"
#include "ERLockItem.generated.h"

/**
 * Base class for items/objects that can be locked and with possibility to unlock with keys (ERKeyItem and derivatives)
 */
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

protected:
	UPROPERTY(VisibleAnywhere, Category="ER")
	bool bLocked{true};
};
