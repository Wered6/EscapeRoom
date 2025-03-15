// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractableActorBase.h"
#include "ERCabinetDrawer.generated.h"

class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERCabinetDrawer : public AERInteractableActorBase
{
	GENERATED_BODY()

public:
	AERCabinetDrawer();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UERLockComponent> LockComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DrawerMesh;
};
