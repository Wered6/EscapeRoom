// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractableActorBase.h"
#include "ERKey.generated.h"

class UERKeyComponent;

UCLASS()
class ESCAPEROOM_API AERKey : public AERInteractableActorBase
{
	GENERATED_BODY()

public:
	AERKey();

	virtual void BeginPlay() override;

	virtual void InteractHoldTriggered_Implementation() override;
	virtual void InteractHoldCompleted_Implementation() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERKeyComponent> KeyComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> KeyMesh;
};
