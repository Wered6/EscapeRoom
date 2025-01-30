// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERCabinetDoor.generated.h"

class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERCabinetDoor : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERCabinetDoor();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Components")
	TObjectPtr<UERLockComponent> LockComponent;
};
