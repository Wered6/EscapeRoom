// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RectLightComponent.h"
#include "GameFramework/Actor.h"
#include "ERCeilingLamp.generated.h"

class URectLightComponent;

UCLASS()
class ESCAPEROOM_API AERCeilingLamp : public AActor
{
	GENERATED_BODY()

public:
	AERCeilingLamp();

	UFUNCTION(BlueprintCallable, Category="ER|Light")
	void TurnLights() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(EditDefaultsOnly, Category="ER|Light", BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TObjectPtr<URectLightComponent> LightLeft;
	UPROPERTY(EditDefaultsOnly, Category="ER|Light")
	TObjectPtr<URectLightComponent> LightRight;
	UPROPERTY(EditDefaultsOnly, Category="ER|Light")
	TObjectPtr<URectLightComponent> HelpLight;
	// TODO add light mask to look like ceiling lamp
	// TODO add sound buzzing when "on"
	// TODO add buzzing/flickering on light left or right, but remember you would have to change also materials emissive colors of them
	// TODO when turns on make it light real, with some delay and flash
	// TODO add spotlight to every room so it wont be completely dark when turning lamp off
};
