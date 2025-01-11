// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "GameFramework/Actor.h"
#include "ERLockItem.generated.h"

/**
 * Base class for items/objects that can be locked and with possibility to unlock with keys (ERKeyItem and derivatives)
 */
UCLASS()
class ESCAPEROOM_API AERLockItem : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERLockItem();

	virtual void Unlock();

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category="ER")
	bool bLocked{true};
};
