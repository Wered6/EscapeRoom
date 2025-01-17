// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeyItem.h"
#include "ERKey.generated.h"

UCLASS()
class ESCAPEROOM_API AERKey : public AERKeyItem
{
	GENERATED_BODY()

public:
	AERKey();

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;
};
