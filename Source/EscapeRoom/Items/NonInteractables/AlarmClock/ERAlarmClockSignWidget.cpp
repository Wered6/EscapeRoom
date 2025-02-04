// Fill out your copyright notice in the Description page of Project Settings.


#include "ERAlarmClockSignWidget.h"
#include "Components/TextBlock.h"

void UERAlarmClockSignWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateText(Text);
	UpdateFont(FontFamily, FontSize);
}

void UERAlarmClockSignWidget::UpdateText(const FString NewText) const
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

void UERAlarmClockSignWidget::UpdateFont(UObject* NewFontFamily, const float NewFontSize) const
{
#pragma region Nullchecks
	if (!NewFontFamily)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|NewFontFamily is nullptr"), *FString(__FUNCTION__))
		return;
	}
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
