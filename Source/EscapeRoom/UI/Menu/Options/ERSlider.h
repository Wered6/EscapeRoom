// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERSlider.generated.h"

class USlider;
class UTextBlock;
class UERButtonTextBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderValueChanged, float, Value);

UCLASS()
class ESCAPEROOM_API UERSlider : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable, Category="ER|Slider")
	FOnSliderValueChanged OnValueChanged;

	UFUNCTION(BlueprintCallable, Category="ER|Slider")
	float GetValue() const;
	UFUNCTION(BlueprintCallable, Category="ER|Slider")
	void SetValue(const float Value) const;

private:
	UFUNCTION()
	void HandleSliderOnValueChanged(float Value);
	UFUNCTION()
	void HandleButtonDecreaseOnPressed();
	UFUNCTION()
	void HandleButtonDecreaseOnHold(const float DeltaSeconds);
	UFUNCTION()
	void HandleButtonIncreaseOnPressed();
	UFUNCTION()
	void HandleButtonIncreaseOnHold(const float DeltaSeconds);

	void UpdateSliderValue(const float Value) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Appearance")
	float StepSizeButton{0.01f};

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<USlider> Slider;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SliderValueText;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UERButtonTextBase> ButtonDecrease;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UERButtonTextBase> ButtonIncrease;

	// TODO do ERSliderBase like ERButtonTextBase
};
