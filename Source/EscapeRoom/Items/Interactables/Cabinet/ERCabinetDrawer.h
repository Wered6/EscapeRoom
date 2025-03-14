// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Components/ERInteractableComponent.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"
#include "ERCabinetDrawer.generated.h"

class UERInteractableComponent;
class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERCabinetDrawer : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERCabinetDrawer();

	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UERLockComponent> LockComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERInteractableComponent> InteractableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DrawerMesh;
};
