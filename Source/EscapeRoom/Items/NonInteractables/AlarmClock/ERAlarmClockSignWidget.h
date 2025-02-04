// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERAlarmClockSignWidget.generated.h"

class UTextBlock;

UCLASS()
class ESCAPEROOM_API UERAlarmClockSignWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable, Category="ER")
	void UpdateText(const FString NewText) const;
	UFUNCTION(BlueprintCallable, Category="ER")
	void UpdateFont(UObject* NewFontFamily, const float NewFontSize) const;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> Sign;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	FString Text;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	TObjectPtr<UObject> FontFamily;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	float FontSize;
};
