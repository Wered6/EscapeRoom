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
	EVC_Off UMETA(DisplayName = "OFF"),
	EVC_White UMETA(DisplayName = "WHITE"),
	EVC_Red UMETA(DisplayName = "RED"),
	EVC_Blue UMETA(DisplayName = "BLUE"),
	EVC_Green UMETA(DisplayName = "GREEN")
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
	void SwitchToNextColor();

	void ShowPickupWidget(const bool bShowWidget) const;

	void SetIsEquipped();

	FORCEINLINE USphereComponent* GetPickUpSphere() const
	{
		return PickupSphere;
	}

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	                     AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex,
	                     bool bFromSweep,
	                     const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                        AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex);

private:
	UFUNCTION(BlueprintCallable)
	void SetUltraVioletColor(EUltraVioletColor UltraVioletColor);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> FlashlightMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> PickupSphere;

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
	FFlashLightColors FlashLightColorRed{};
	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorBlue{};
	UPROPERTY(EditDefaultsOnly)
	FFlashLightColors FlashLightColorGreen{};

	UPROPERTY(VisibleAnywhere)
	EUltraVioletColor CurrentColor{EUltraVioletColor::EVC_Off};

	UPROPERTY(VisibleAnywhere)
	bool bIsEquipped{};
};
