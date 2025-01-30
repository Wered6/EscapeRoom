// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERCabinetDrawer.generated.h"

class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERCabinetDrawer : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERCabinetDrawer();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Components")
	TObjectPtr<UERLockComponent> LockComponent;
};
