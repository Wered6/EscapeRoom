// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERDoor.generated.h"

class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERDoor : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERDoor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="ER|Audio")
	TObjectPtr<USoundBase> UnlockSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> HandleMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Components")
	TObjectPtr<UERLockComponent> LockComponent;

private:
	void PlayUnlockSound();
};
