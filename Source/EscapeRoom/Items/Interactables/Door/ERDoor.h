// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractableActorBase.h"
#include "ERDoor.generated.h"

class UERLockComponent;

UCLASS()
class ESCAPEROOM_API AERDoor : public AERInteractableActorBase
{
	GENERATED_BODY()

public:
	AERDoor();

	virtual void BeginPlay() override;

private:
	void PlayUnlockSound();

	UPROPERTY(EditDefaultsOnly, Category="ER|Audio")
	TObjectPtr<USoundBase> UnlockSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UERLockComponent> LockComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FrameMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> HandleMesh;
};
