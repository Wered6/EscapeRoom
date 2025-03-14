// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"
#include "ERFlashlight.generated.h"

struct FUVGlassData;
class UERInteractableComponent;
class USpotLightComponent;

DECLARE_DELEGATE(FOnFlashlightEquipped)

UCLASS()
class ESCAPEROOM_API AERFlashlight : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERFlashlight();

protected:
	virtual void BeginPlay() override;

public:
	void TurnOn() const;
	void TurnOff() const;

	void SetUltraVioletColor(const FUVGlassData& UVGlassData);

	/**
	 * Overriding InteractPressTriggered function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractPressTriggered_Implementation() override;

	FOnFlashlightEquipped OnFlashlightEquipped;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpotLightComponent> SpotLight;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpotLightComponent> SpotLightGlow;

	UPROPERTY(EditDefaultsOnly, Category="ER|UV")
	TObjectPtr<UMaterialInstance> PostProcessMask;
	// TODO add light mask to look like flashlight

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERInteractableComponent> InteractableComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FlashlightMesh;
};
