// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "ERCharacter.generated.h"

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
	virtual void Tick(float DeltaSeconds) override;

private:
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

	void EnterDefaultInputMode() const;
	void EnterKeypadInputMode() const;

protected:
	/**
	 * Call for default movement action
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * Call for default looking action
	 */
	void Look(const FInputActionValue& Value);

	/**
	 * Call for default change color flashlight action
	 */
	void FlashlightChangeColorButtonPressed();

	/**
	 * Call for default interact action
	 */
	void Interact();

	/**
	 * Call for keypad move action
	 */
	void KeypadMove(const FInputActionValue& Value);

	/**
	 * Call for keypad accept button pressed action
	 */
	void KeypadButtonPressed();

	/**
	 * Call for keypad accept button released action
	 */
	void KeypadButtonReleased();

	/**
	 * Call for keypad exit action
	 */
	void KeypadExit();

private:
	/**
	 * Default Mapping Context
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Default")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/**
	 * Default Move Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Default")
	TObjectPtr<UInputAction> MoveAction;

	/**
	 * Default Look Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Default")
	TObjectPtr<UInputAction> LookAction;

	/**
	 * Default Flashlight Change Color Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Default")
	TObjectPtr<UInputAction> FlashlightChangeColorAction;

	/**
	 * Default Interact Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Default")
	TObjectPtr<UInputAction> InteractAction;

	/**
	 * Keypad Mapping Context
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Keypad")
	TObjectPtr<UInputMappingContext> KeypadMappingContext;

	/**
	 * Keypad Move Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Keypad")
	TObjectPtr<UInputAction> KeypadMoveAction;

	/**
	 * Keypad Accept Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Keypad")
	TObjectPtr<UInputAction> KeypadButtonAction;

	/**
	 * Keypad exit Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Keypad")
	TObjectPtr<UInputAction> KeypadExitAction;

#pragma endregion

#pragma region Interact

public:
	FORCEINLINE void SetCanCheckInteraction(const bool bValue)
	{
		bCanCheckInteraction = bValue;
	}

	void SetIndicatorVisibility(const bool bVisible) const;

private:
	void PerformInteractionCheck();

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractableActor;
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> InteractableHitComponent;

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	float InteractionDistance{200.f};

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	bool bCanCheckInteraction{true};

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

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight")
	TObjectPtr<AERFlashlight> EquippedFlashlight;

#pragma endregion
};
