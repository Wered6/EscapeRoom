// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "ERCharacter.generated.h"

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
	virtual void Tick(float DeltaSeconds) override;

public:
	void SetLimitMovement(const bool bLimit);

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
	void EnterKeypadInputMode() const;
	void ExitKeypadInputMode() const;

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

	/**
	 * Call for Gameplay interact action
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
	/**
	 * Gameplay Interact Input Action
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Gameplay")
	TObjectPtr<UInputAction> InteractAction;

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

	// TODO make InteractComponent
public:
	/**
	 * Stops performing interaction check but InteractableActor stays set
	 */
	FORCEINLINE void SetCanCheckInteraction(const bool bValue)
	{
		bCanCheckInteraction = bValue;
	}

	void SetIndicatorVisibility(const bool bVisible) const;

private:
	void PerformInteractionCheck();
	void ClearInteraction();

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

	void CollectUVGlass(const FUVGlassData& UVGlassData);

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight")
	TObjectPtr<AERFlashlight> EquippedFlashlight;

	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight")
	TArray<FUVGlassData> CollectedUVGlasses;
	uint8 CollectedUVGlassesIndex{};

#pragma endregion
};
