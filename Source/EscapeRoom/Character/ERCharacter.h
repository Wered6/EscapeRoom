// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ERCharacter.generated.h"

struct FInputActionValue;
class AFlashlight;
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
	virtual void Tick(float DeltaTime) override;

public:
	void SetOverlappingFlashlight(AFlashlight* Flashlight);

	FORCEINLINE bool HasFlashlight() const
	{
		return EquippedFlashlight ? true : false;
	}

	FORCEINLINE AFlashlight* GetEquippedFlashlight() const
	{
		return EquippedFlashlight;
	}

protected:
	virtual void NotifyControllerChanged() override;

private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> Camera1P;

	UPROPERTY()
	TObjectPtr<AFlashlight> OverlappingFlashlight;

	UPROPERTY()
	TObjectPtr<AFlashlight> EquippedFlashlight;

#pragma region Input

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for equip input */
	void EquipButtonPressed();

private:
	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> LookAction;

	/** Equip Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> EquipAction;

#pragma endregion
};
