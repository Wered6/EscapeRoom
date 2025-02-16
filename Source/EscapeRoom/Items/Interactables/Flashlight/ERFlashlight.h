// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERUVGlass.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERFlashlight.generated.h"

class USpotLightComponent;

DECLARE_DELEGATE(FOnFlashlightEquipped)

UCLASS()
class ESCAPEROOM_API AERFlashlight : public AERInteractableActor
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
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

	FOnFlashlightEquipped OnFlashlightEquipped;

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight|UV")
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight|UV")
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight|UV")
	TObjectPtr<USpotLightComponent> SpotLightGlow;

	UPROPERTY(EditDefaultsOnly, Category="ER|Flashlight|UV|DynamicMaterial")
	TObjectPtr<UMaterialInstance> PostProcessMask;
	// TODO add light mask to look like flashlight
};
