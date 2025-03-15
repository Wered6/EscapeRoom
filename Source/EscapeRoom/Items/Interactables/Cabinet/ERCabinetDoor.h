// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractableActorBase.h"
#include "ERCabinetDoor.generated.h"

class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERCabinetDoor : public AERInteractableActorBase
{
	GENERATED_BODY()

public:
	AERCabinetDoor();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UERLockComponent> LockComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorMesh;
};
