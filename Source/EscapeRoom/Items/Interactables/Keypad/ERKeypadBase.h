// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERKeypadBase.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class URectLightComponent;

UENUM(BlueprintType)
enum class EKeypadButtonValue : uint8
{
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	DEL,
	OK
};

USTRUCT(BlueprintType)
struct FKeypadButton
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Keypad|Button")
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Button")
	uint8 Value{};
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Button")
	EKeypadButtonValue KeypadButtonValue{};
};

USTRUCT()
struct FKeypadButtonArray
{
	GENERATED_BODY()

	FKeypadButtonArray()
	{
	}

	explicit FKeypadButtonArray(const FKeypadButton& Button)
	{
		ButtonArray.Add(Button);
	}

	FKeypadButtonArray(const FKeypadButton& Button1, const FKeypadButton& Button2, const FKeypadButton& Button3)
	{
		ButtonArray.Add(Button1);
		ButtonArray.Add(Button2);
		ButtonArray.Add(Button3);
	}

	TArray<FKeypadButton> ButtonArray;
};

enum class ELedColor : uint8
{
	Green,
	Red
};

// TODO make it multicast
DECLARE_DELEGATE(FOnFinishProcessing)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnKeypadButtonPressed, EKeypadButtonValue, uint8)

UCLASS()
class ESCAPEROOM_API AERKeypadBase : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERKeypadBase();

protected:
	virtual void BeginPlay() override;

public:
	/**
	* Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor in KeyItem)
	*/
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

protected:
	void EnterKeypadMode();
	void ExitKeypadMode() const;

	void LedFlash(const ELedColor LedColor, float FlashTime);

	UFUNCTION(BlueprintImplementableEvent, Category="ER|Keypad|Button")
	void PlayButtonAnimation();
	UFUNCTION(BlueprintImplementableEvent, Category="ER|Keypad|Button")
	void ReverseButtonAnimation();

	/**
	 * 0 - 9 is the same
	 * DEL is 10, OK is 20
	 */
	TArray<FKeypadButtonArray> Button2DArray;
	bool bCanNavigate{true};
	bool bCanPressButton{true};
	bool bProcessing{true};
	UPROPERTY(BlueprintReadOnly, Category="ER|Keypad|Button")
	FKeypadButton SelectedButton;

	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedShortFlashTime{0.1f};
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedLongFlashTime{1.f};

	FOnKeypadButtonPressed OnKeypadButtonPressed;
	FOnFinishProcessing OnFinishProcessing;

private:
	void PopulateButton2DArray();

	/**
	* Adjust Player and it's Camera location and rotation so it looks at keypad.
	*/
	void LookAtKeypad() const;

	/**
	 * Updates SelectedButton variable (struct containing mesh and value of button) and outline it's mesh
	 */
	void UpdateSelectedButton();

	void StartProcessing();
	void LedBlinking();

	/**
	 * If true look at rotation at keypad, if false look in front of
	 */
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Utility")
	bool bLookDirectlyAtKeypad{true};

	/**
	 * Player location scene from which player will look at Keypad after interacting with it
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Utility")
	TObjectPtr<USceneComponent> PlayerLocationScene;

	int8 Button2DArrayXIndex{2};
	int8 Button2DArrayYIndex{3};

	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Leds")
	TObjectPtr<UMaterialInstanceDynamic> GreenLedDynMat;
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Leds")
	TObjectPtr<UMaterialInstanceDynamic> RedLedDynMat;
	FTimerHandle GreenLedEmiTimerHandle;
	FTimerHandle RedLedEmiTimerHandle;

	FTimerHandle LedBlinkTimerHandle;
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedBlinkInterval{0.5f};
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Leds")
	uint8 LedBlinkLoopCounter{};
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	uint8 NumberOfBlinks{5};

	UPROPERTY(BlueprintReadOnly, Category="ER|Keypad|Button", meta=(AllowPrivateAccess=true))
	float ButtonDepth{4.f};

	UPROPERTY(EditAnywhere, Category="ER|Keypad|Light")
	TObjectPtr<URectLightComponent> HelpLight;

	// TODO convert all logic beside keypad sending which key was pressed to anything that uses keypad

#pragma region Input

protected:
	/**
	* Call for keypad move action
	*/
	virtual void Navigate(const FInputActionValue& Value);
	/**
	 * Call for keypad button pressed action
	 */
	virtual void ButtonPressed();
	/**
	 * Call for keypad button released action
	 */
	void ButtonReleased();
	/**
	 * Call for keypad exit action
	 */
	void Exit();

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputMappingContext> KeypadMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputAction> KeypadNavigateAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputAction> KeypadButtonAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputAction> KeypadExitAction;

#pragma endregion

#pragma region Audio

	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Audio")
	TObjectPtr<USoundBase> ShortGreenLedSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Audio")
	TObjectPtr<USoundBase> ShortRedLedSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Audio")
	TObjectPtr<USoundBase> LongGreenLedSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Audio")
	TObjectPtr<USoundBase> LongRedLedSound;


#pragma endregion

#pragma region Meshes

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button0Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button1Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button2Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button3Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button4Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button5Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button6Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button7Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button8Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> Button9Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonDELMesh;
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
	TObjectPtr<UStaticMeshComponent> GreenLedMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RedLedMesh;

#pragma endregion
};
