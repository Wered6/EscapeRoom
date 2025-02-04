// Fill out your copyright notice in the Description page of Project Settings.


#include "ERAlarmClockWidget.h"
#include "ERAlarmClockSignWidget.h"

void UERAlarmClockWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateTime(MinutesInit, SecondsInit);
}

void UERAlarmClockWidget::UpdateTime(const uint8 Minutes, const uint8 Seconds) const
{
#pragma region Nullchecks
	if (!MinutesWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|MinutesWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!SecondsWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SecondsWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	if (Minutes > 59)
	{
		UE_LOG(LogTemp, Warning, TEXT("Minutes is %d, max is 59"), Minutes)
		return;
	}
	if (Seconds > 59)
	{
		UE_LOG(LogTemp, Warning, TEXT("Seconds is %d, max is 59"), Seconds)
		return;
	}

	MinutesWidget->UpdateText(FString(Minutes < 10 ? "0" : "") + FString::FromInt(Minutes));
	SecondsWidget->UpdateText(FString(Seconds < 10 ? "0" : "") + FString::FromInt(Seconds));
}
