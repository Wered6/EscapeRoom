// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadInteface.h"
#include "EscapeRoom/Items/Interactables/Keys/ERKeyItem.h"
#include "ERKeypad.generated.h"


USTRUCT(BlueprintType)
struct FKeypadButton
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Keypad|Button")
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Button")
	uint8 Value{};
};

USTRUCT()
struct FKeypadButtonArray
{
	GENERATED_BODY()

	FKeypadButtonArray()
	{
	}

	FKeypadButtonArray(const FKeypadButton& Button1, const FKeypadButton& Button2, const FKeypadButton& Button3)
	{
		ButtonArray.Add(Button1);
		ButtonArray.Add(Button2);
		ButtonArray.Add(Button3);
	}

	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Button")
	TArray<FKeypadButton> ButtonArray;
};

class URectLightComponent;

UCLASS()
class ESCAPEROOM_API AERKeypad : public AERKeyItem, public IERKeypadInterface
{
	GENERATED_BODY()

public:
	AERKeypad();

protected:
	virtual void BeginPlay() override;

public:
	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor in KeyItem)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

	/**
	 * Overriding KeypadMove function from ERKeypadInterface
	 */
	virtual void KeypadMove_Implementation(const FVector2D& MovementVector) override;
	/**
	 * Overriding KeypadAcceptButtonPressed function from ERKeypadInterface
	 */
	virtual void KeypadAcceptButtonPressed_Implementation() override;
	/**
	 * Overriding KeypadAcceptButtonReleased function from ERKeypadInterface
	 */
	virtual void KeypadAcceptButtonReleased_Implementation() override;
	/**
	 * Overriding KeypadExit function from ERKeypadInterface
	 */
	virtual void KeypadExit_Implementation() override;

private:
	void PopulateButton2DArray();

	void EnterKeypadMode();
	void EnterDefaultMode() const;

	/**
	 * Adjust Player and it's Camera location and rotation so it looks at keypad.
	 */
	void LookAtKeypad() const;

	/**
	 * Updates SelectedButton variable (struct containing mesh and value of button) and outline it's mesh
	 */
	void UpdateSelectedButton();

	/**
	 * Start loop timer of CheckingPassword function
	 */
	void StartCheckingPassword();
	void CheckingPassword();
	void CheckPassword();

	void GreenLedFlash(const float FlashTime);
	void RedLedFlash(const float FlashTime);

	void ResetGreenLedEmissive();
	void ResetRedLedEmissive();
	void ResetLedEmissive(UStaticMeshComponent* LedMesh);

	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Utility")
	TObjectPtr<USceneComponent> PlayerLocationScene;

	/**
	 * 0 - 9 is the same
	 * DEL is 10, OK is 20
	 */
	TArray<FKeypadButtonArray> Button2DArray;
	int8 Button2DArrayX{1};
	int8 Button2DArrayY{1};
	bool bCanNavigate{true};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Keypad|Button", meta=(AllowPrivateAccess="true"))
	FKeypadButton SelectedButton;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Button")
	TObjectPtr<UMaterialInterface> OutlineButtonMaterial;

	UPROPERTY(EditAnywhere, Category="ER|Keypad|Password")
	FString Password;
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Password")
	FString UserPassword;

	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Leds")
	TObjectPtr<UMaterialInstance> LedMaterial;

	FTimerHandle GreenLedEmissiveTimerHandle;
	FTimerHandle RedLedEmissiveTimerHandle;
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedShortFlashTime{0.1f};
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedLongFlashTime{1.f};

	FTimerHandle LedBlinkTimerHandle;
	/**
	 * Interval between blinks when checking password
	 */
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedBlinkInterval{0.5f};
	/**
	 * Counter of blinks when checking password
	 */
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Leds")
	uint8 LoopsCounter{};
	/**
	 * Loops of blinking when checking password
	 */
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	uint8 BlinkLoops{5};

#pragma region Meshes

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonOneMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonTwoMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonThreeMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonFourMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonFiveMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonSixMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonSevenMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonEightMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonNineMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonDelMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonZeroMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonOKMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewL1Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewL2Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewR1Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewR2Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ShieldLogoMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> LedGreenMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> LedRedMesh;

#pragma endregion
// TODO try to combine meshes and textures to lower the size
};
