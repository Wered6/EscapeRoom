// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERAlarmClockWidget.generated.h"


class AERAlarmClock;
class UERAlarmClockSignWidget;
class UTextBlock;

UCLASS()
class ESCAPEROOM_API UERAlarmClockWidget : public UUserWidget
{
	GENERATED_BODY()

	friend AERAlarmClock;

public:
	virtual void NativePreConstruct() override;

private:
	void UpdateTime(const uint8 Minutes, const uint8 Seconds) const;

	uint8 MinutesInit;
	uint8 SecondsInit;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERAlarmClockSignWidget> MinutesWidget;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERAlarmClockSignWidget> SecondsWidget;
};
