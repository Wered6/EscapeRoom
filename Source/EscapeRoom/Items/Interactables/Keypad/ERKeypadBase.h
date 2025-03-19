// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractablePawnBase.h"
#include "ERKeypadBase.generated.h"

class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class URectLightComponent;

UENUM(BlueprintType)
enum class EKeypadButtonName : uint8
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
	EKeypadButtonName Name{};
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
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnKeypadButtonPressed, EKeypadButtonName, uint8)

UCLASS()
class ESCAPEROOM_API AERKeypadBase : public AERInteractablePawnBase
{
	GENERATED_BODY()

public:
	AERKeypadBase();

protected:
	virtual void BeginPlay() override;

protected:
	void EnterKeypadMode();
	void ExitKeypadMode();

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
	 * Updates SelectedButton variable (struct containing mesh and value of button) and outline it's mesh
	 */
	void UpdateSelectedButton();

	void StartProcessing();
	void LedBlinking();

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
	float ButtonDepthScale{4.f};

	UPROPERTY(EditAnywhere)
	TObjectPtr<URectLightComponent> HelpLight;

	// TODO convert all logic beside keypad sending which key was pressed to anything that uses keypad

#pragma region Interact

public:
	virtual void InteractPressStarted_Implementation(AActor* OtherInstigator) override;
	virtual void InteractPressTriggered_Implementation() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> InteractArea;

	UPROPERTY()
	TObjectPtr<AActor> InteractInstigator;

#pragma endregion

#pragma region Camera

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

#pragma endregion

#pragma region Input

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	/**
	* Bind to NavigateAction
	*/
	virtual void Navigate(const FInputActionValue& Value);
	/**
	 * Bind to ButtonAction
	 */
	virtual void ButtonPressed();
	/**
	 * Bind to ButtonAction
	 */
	void ButtonReleased();
	/**
	 * Bind to ExitAction
	 */
	void Exit();

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputMappingContext> KeypadMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputAction> NavigateAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputAction> ButtonAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Keypad|Input")
	TObjectPtr<UInputAction> ExitAction;

#pragma endregion

#pragma region Audio

private:
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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BodyMesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button0Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button1Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button2Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button3Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button4Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button5Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button6Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button7Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button8Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Button9Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ButtonDELMesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ButtonOKMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ScrewL1Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ScrewL2Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ScrewR1Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ScrewR2Mesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ShieldLogoMesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> GreenLedMesh;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> RedLedMesh;

#pragma endregion
};
