// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"
#include "ERCabinetDoor.generated.h"

class UERInteractableComponent;
class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERCabinetDoor : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERCabinetDoor();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UERLockComponent> LockComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERInteractableComponent> InteractableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorMesh;
};
