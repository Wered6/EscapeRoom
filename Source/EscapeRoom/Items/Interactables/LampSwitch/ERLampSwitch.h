// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractableActorBase.h"
#include "ERLampSwitch.generated.h"

class AERCeilingLamp;

UCLASS()
class ESCAPEROOM_API AERLampSwitch : public AERInteractableActorBase
{
	GENERATED_BODY()

public:
	AERLampSwitch();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="ER|LampSwitch")
	TObjectPtr<AERCeilingLamp> Lamp;
	// TODO add sound click switch

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FrameMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> SwitchMesh;
};
