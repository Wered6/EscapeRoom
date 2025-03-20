// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	/**
	 * First person camera
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ER|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> Camera1P;

#pragma endregion

#pragma region Input

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	/**
	 * Bind to MoveAction
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * Bind to LookAction
	 */
	void Look(const FInputActionValue& Value);

	/**
	 * Bind FlashlightChangeColorAction
	 */
	void UseFlashlight();

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
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

	void CollectUVGlassData(const FUVGlassData& UVGlassData);

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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERInteractComponent> InteractComponent;

#pragma endregion
};
