// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERFlashlightWidget.generated.h"

enum class EUltraVioletColor : uint8;

class UImage;

UCLASS()
class ESCAPEROOM_API UERFlashlightWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// void OutlineUltraVioletColor(const EUltraVioletColor UltraVioletColor) const;

private:
	void OutlineIcon(UImage* Icon, const bool bOutline = true) const;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> FlashlightIcon_OFF;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> FlashlightIcon_WHITE;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> FlashlightIcon_RED;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> FlashlightIcon_GREEN;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> FlashlightIcon_BLUE;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> FlashlightIcon;

	// TODO add key so player knows what to press
};
