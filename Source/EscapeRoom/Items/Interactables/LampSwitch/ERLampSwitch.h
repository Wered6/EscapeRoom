// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERLampSwitch.generated.h"

class AERCeilingLamp;

UCLASS()
class ESCAPEROOM_API AERLampSwitch : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERLampSwitch();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|LampSwitch|Mesh")
	TObjectPtr<UStaticMeshComponent> SwitchMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="ER|LampSwitch")
	TObjectPtr<AERCeilingLamp> Lamp;
	// TODO add sound click switch
};
