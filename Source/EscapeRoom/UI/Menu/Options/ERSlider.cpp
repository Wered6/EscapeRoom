// Fill out your copyright notice in the Description page of Project Settings.


#include "ERSlider.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "EscapeRoom/UI/ERButtonTextBase.h"

void UERSlider::NativeConstruct()
{
	Super::NativeConstruct();

	HandleSliderOnValueChanged(Slider->GetValue());

	Slider->OnValueChanged.AddDynamic(this, &UERSlider::HandleSliderOnValueChanged);
	ButtonDecrease->OnPressed.AddDynamic(this, &UERSlider::HandleButtonDecreaseOnPressed);
	ButtonDecrease->OnHold.AddDynamic(this, &UERSlider::HandleButtonDecreaseOnHold);
	ButtonIncrease->OnPressed.AddDynamic(this, &UERSlider::HandleButtonIncreaseOnPressed);
	ButtonIncrease->OnHold.AddDynamic(this, &UERSlider::HandleButtonIncreaseOnHold);
}

float UERSlider::GetValue() const
{
	return Slider->GetValue();
}

void UERSlider::SetValue(const float Value) const
{
	Slider->SetValue(Value);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERSlider::HandleSliderOnValueChanged(const float Value)
{
	OnValueChanged.Broadcast(Value);

	const int64 SliderValue = Value * 100;
	SliderValueText->SetText(FText::AsNumber(SliderValue));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERSlider::HandleButtonDecreaseOnPressed()
{
	UpdateSliderValue(-StepSizeButton);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERSlider::HandleButtonDecreaseOnHold(const float DeltaSeconds)
{
	UpdateSliderValue(-StepSizeButton);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERSlider::HandleButtonIncreaseOnPressed()
{
	UpdateSliderValue(StepSizeButton);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERSlider::HandleButtonIncreaseOnHold(const float DeltaSeconds)
{
	UpdateSliderValue(StepSizeButton);
}

void UERSlider::UpdateSliderValue(const float Value) const
{
	const float UpdatedValue{Slider->GetValue() + Value};
	Slider->SetValue(FMath::Clamp(UpdatedValue, 0.f, 100.f));
}
