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

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

private:
	UPROPERTY(EditInstanceOnly, Category="ER")
	TObjectPtr<AERLockItem> LockedItem;
};
