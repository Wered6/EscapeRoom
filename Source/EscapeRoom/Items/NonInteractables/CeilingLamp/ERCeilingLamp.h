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

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category="ER|CeilingLamp|Light")
	void TurnLights() const;

private:
	void UpdateLightsEmissive() const;

	UPROPERTY(EditAnywhere, Category="ER|CeilingLamp|Light")
	bool bLightOn{false};
	UPROPERTY(EditAnywhere, Category="ER|CeilingLamp|Light")
	float EmissiveStrength{20.f};

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> LightDynMat;

	UPROPERTY(VisibleAnywhere, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> LightRight;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> LightLeft;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> HelpLight;
	// TODO add light mask to look like ceiling lamp
	// TODO add sound buzzing when "on"
	// TODO add buzzing/flickering on light left or right, but remember you would have to change also materials emissive colors of them
	// TODO when turns on make it light real, with some delay and flash
};
