// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERKey.generated.h"

class UERKeyComponent;

UCLASS()
class ESCAPEROOM_API AERKey : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERKey();

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Components")
	TObjectPtr<UERKeyComponent> KeyComponent;
};
