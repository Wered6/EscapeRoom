// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "ERFlashlight.generated.h"

class USpotLightComponent;
class UWidgetComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EUltraVioletColor : uint8
{
	EVC_Off UMETA(DisplayName = "OFF"),
	EVC_White UMETA(DisplayName = "WHITE"),
	EVC_Red UMETA(DisplayName = "RED"),
	EVC_Green UMETA(DisplayName = "GREEN"),
	EVC_Blue UMETA(DisplayName = "BLUE")
};

USTRUCT(BlueprintType)
struct FFlashLightColors
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FLinearColor BaseLight{};
	UPROPERTY(EditDefaultsOnly)
	FLinearColor GlowLight{};
	UPROPERTY(EditDefaultsOnly)
	float UltraVioletValue{};
};

UCLASS()
class ESCAPEROOM_API AERFlashlight : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERFlashlight();

protected:
	virtual void BeginPlay() override;

public:
	void SwitchToNextColor();

	FORCEINLINE EUltraVioletColor GetCurrentColor() const
	{
		return CurrentColor;
	}

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

private:
	UFUNCTION(BlueprintCallable, Category="ER|UV")
	void SetUltraVioletColor(EUltraVioletColor UltraVioletColor);

	UPROPERTY(VisibleAnywhere, Category="ER|UV")
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(VisibleAnywhere, Category="ER|UV")
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(VisibleAnywhere, Category="ER|UV")
	TObjectPtr<USpotLightComponent> SpotLightGlow;

	UPROPERTY(EditDefaultsOnly, Category="ER|UV")
	TObjectPtr<UMaterialInstance> PostProcessMask;

	UPROPERTY(EditDefaultsOnly, Category="ER|UV")
	FFlashLightColors FlashLightColorRed{};
	UPROPERTY(EditDefaultsOnly, Category="ER|UV")
	FFlashLightColors FlashLightColorGreen{};
	UPROPERTY(EditDefaultsOnly, Category="ER|UV")
	FFlashLightColors FlashLightColorBlue{};

	UPROPERTY(VisibleAnywhere, Category="ER|UV")
	EUltraVioletColor CurrentColor{EUltraVioletColor::EVC_Off};
	// TODO add light mask to look like flashlight
};
