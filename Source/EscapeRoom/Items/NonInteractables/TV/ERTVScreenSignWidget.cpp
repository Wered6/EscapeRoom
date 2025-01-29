// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTVScreenSignWidget.h"
#include "Components/TextBlock.h"


void UERTVScreenSignWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateText(Text);
	UpdateFont(FontFamily, FontSize);

	if (bBlinkFromStart)
	{
		PlayBlinkAnimation();
	}
}

void UERTVScreenSignWidget::UpdateText(const FString NewText) const
{
#pragma region Nullchecks
	if (!Sign)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Sign is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Sign->SetText(FText::FromString(NewText));
}

auto UERTVScreenSignWidget::UpdateFont(UObject* NewFontFamily, const float NewFontSize) const -> void
{
#pragma region Nullchecks
	if (!Sign)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Sign is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	FSlateFontInfo SlateFontInfo;
	SlateFontInfo.FontObject = NewFontFamily;
	SlateFontInfo.Size = NewFontSize;

	Sign->SetFont(SlateFontInfo);
}

void UERTVScreenSignWidget::PlayBlinkAnimation()
{
#pragma region Nullchecks
	if (!BlinkAnimation)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|BlinkAnimation is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	PlayAnimation(BlinkAnimation, 0.f, 0.f);
}

void UERTVScreenSignWidget::StopBlinkAnimation()
{
#pragma region Nullchecks
	if (!BlinkAnimation)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|BlinkAnimation is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	StopAnimation(BlinkAnimation);
}
