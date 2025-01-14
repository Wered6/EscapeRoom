// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ERCharacter.generated.h"

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
	virtual void NotifyControllerChanged() override;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ER|Mesh", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ER|Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> Camera1P;

#pragma region Input

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for flashlight input */
	void FlashlightButtonPressed();

	/** Called for interact input */
	void Interact();

private:
	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputAction> LookAction;

	/** Flashlight Input Action */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputAction> FlashlightAction;

	/** Interact Input Action */
	UPROPERTY(EditDefaultsOnly, Category="ER|Input")
	TObjectPtr<UInputAction> InteractAction;

#pragma endregion

#pragma region Interact

private:
	void PerformInteractionCheck();

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractableActor;

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	float InteractionDistance{200.f};

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
	// TODO Adjust center of flashlight to center of screen
	UPROPERTY(VisibleAnywhere, Category="ER|Flashlight")
	TObjectPtr<AERFlashlight> EquippedFlashlight;

#pragma endregion
};
