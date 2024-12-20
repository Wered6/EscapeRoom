// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

class USpotLightComponent;
class UWidgetComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EUltraVioletColor : uint8
{
	EVC_Red UMETA(DisplayName = "Red"),
	EVC_Blue UMETA(DisplayName = "Blue"),
	EVC_Green UMETA(DisplayName = "Green")
};

USTRUCT(BlueprintType)
struct FFlashLightColors
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FLinearColor BaseLight;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor GlowLight;
};

UCLASS()
class ESCAPEROOM_API AFlashlight : public AActor
{
	GENERATED_BODY()

public:
	AFlashlight();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetUltraVioletColor(EUltraVioletColor UltraVioletColor);

	void ShowPickupWidget(const bool bShowWidget) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FlashlightMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> PickUpSphere;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> PickupWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCapture;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpotLightComponent> SpotLightGlow;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> PostProcessMask;

	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorRed;
	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorBlue;
	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorGreen;
};
