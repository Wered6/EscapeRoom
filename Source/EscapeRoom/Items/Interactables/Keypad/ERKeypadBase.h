// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadInteface.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERKeypadBase.generated.h"

class URectLightComponent;
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

DECLARE_DELEGATE(FOnEndLedBlinking)

UCLASS()
class ESCAPEROOM_API AERKeypadBase : public AERInteractableActor, public IERKeypadInterface
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

	/**
	 * Overriding KeypadMove function from ERKeypadInterface
	 */
	virtual void KeypadMove_Implementation(const FVector2D& MovementVector) override;
	/**
	 * Overriding KeypadAcceptButtonPressed function from ERKeypadInterface
	 */
	virtual void KeypadButtonPressed_Implementation() override;
	/**
	 * Overriding KeypadAcceptButtonReleased function from ERKeypadInterface
	 */
	virtual void KeypadButtonReleased_Implementation() override;
	/**
	 * Overriding KeypadExit function from ERKeypadInterface
	 */
	virtual void KeypadExit_Implementation() override;

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
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Keypad|Button", meta=(AllowPrivateAccess=true))
	FKeypadButton SelectedButton;

	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedShortFlashTime{0.1f};
	UPROPERTY(EditAnywhere, Category="ER|Keypad|Leds")
	float LedLongFlashTime{1.f};

	FOnEndLedBlinking OnEndLedBlinking;

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

	void StartLedBlinking();
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

	int8 Button2DArrayX{2};
	int8 Button2DArrayY{3};

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
