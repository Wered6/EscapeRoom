// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "ERCharacter.generated.h"

class UERInteractComponent;
struct FUVGlassData;
class AERPlayerController;
struct FInputActionValue;
class AERFlashlight;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;

UCLASS()
class ESCAPEROOM_API AERCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AERCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyControllerChanged() override;

public:
	void SetLimitMovement(const bool bLimit);

	void SetIndicatorVisibility(const bool bVisible) const;

private:
	bool bLimitMovement{};

	/**
	 * Pawn mesh: 1st person view (arms; seen only by self)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ER|Mesh", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY()
	TObjectPtr<AERPlayerController> PlayerController;

#pragma region Camera

public:
	void ResetCameraTransform() const;

private:
	/**
	 * First person camera
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ER|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> Camera1P;

	UPROPERTY(VisibleAnywhere, Category="ER|Camera")
	FTransform CameraDefaultTransform;

#pragma endregion

#pragma region Input

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnterGameplayAndMenuInputMode() const;
	void EnterGameplayInputMode() const;
	void ExitGameplayInputMode() const;

protected:
	/**
	 * Call for Pause action
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerPauseMenu();

	/**
	 * Call for Gameplay movement action
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * Call for Gameplay looking action
	 */
	void Look(const FInputActionValue& Value);

	/**
	 * Call for Gameplay change color flashlight action
	 */
	void UseFlashlight();

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Menu")
	TObjectPtr<UInputMappingContext> MenuMappingContext;
	/**
	 * Pause Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Menu")
	TObjectPtr<UInputAction> PauseMenu;

	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Gameplay")
	TObjectPtr<UInputMappingContext> GameplayMappingContext;
	/**
	 * Gameplay Move Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Gameplay")
	TObjectPtr<UInputAction> MoveAction;
	/**
	 * Gameplay Look Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Gameplay")
	TObjectPtr<UInputAction> LookAction;
	/**
	 * Gameplay Flashlight Change Color Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Gameplay")
	TObjectPtr<UInputAction> FlashlightChangeColorAction;

#pragma endregion

#pragma region Flashlight

public:
	FORCEINLINE bool HasFlashlight() const
	{
		return EquippedFlashlight ? true : false;
	}

	FORCEINLINE AERFlashlight* GetEquippedFlashlight() const
	{
		return EquippedFlashlight;
	}

	void EquipFlashlight(AERFlashlight* Flashlight);

	void CollectUVGlass(const FUVGlassData& UVGlassData);

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight")
	TObjectPtr<AERFlashlight> EquippedFlashlight;

	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight")
	TArray<FUVGlassData> CollectedUVGlasses;
	uint8 CollectedUVGlassesIndex{};

#pragma endregion

#pragma region Interact

public:
	FORCEINLINE UERInteractComponent* GetInteractComponent()
	{
		return InteractComponent;
	}

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<UERInteractComponent> InteractComponent;

#pragma endregion
};
