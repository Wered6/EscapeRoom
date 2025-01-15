// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "ERLampSwitch.generated.h"

class AERCeilingLamp;

UCLASS()
class ESCAPEROOM_API AERLampSwitch : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERLampSwitch();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> SwitchMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="ER|Pick Actor")
	TObjectPtr<AERCeilingLamp> Lamp;
	// TODO add sound click switch
};
