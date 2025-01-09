// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Interact/ERInteractableActor.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

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
};

// TODO Add prefix ER
UCLASS()
class ESCAPEROOM_API AFlashlight : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AFlashlight();

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
	UFUNCTION(BlueprintCallable)
	void SetUltraVioletColor(EUltraVioletColor UltraVioletColor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> FlashlightMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpotLightComponent> SpotLightGlow;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> PostProcessMask;

	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorRed{};
	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorBlue{};
	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorGreen{};

	UPROPERTY(VisibleAnywhere)
	EUltraVioletColor CurrentColor{EUltraVioletColor::EVC_Off};
};
