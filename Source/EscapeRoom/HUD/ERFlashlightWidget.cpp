// Fill out your copyright notice in the Description page of Project Settings.


#include "ERFlashlightWidget.h"
#include "Components/Image.h"
#include "EscapeRoom/Items/Interactables/Flashlight/ERFlashlight.h"

// void UERFlashlightWidget::OutlineUltraVioletColor(const EUltraVioletColor UltraVioletColor) const
// {
// #pragma region Nullchecks
// 	if (!FlashlightIcon_OFF)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightIcon_OFF is nullptr"), *FString(__FUNCTION__))
// 		return;
// 	}
// 	if (!FlashlightIcon_WHITE)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightIcon_WHITE is nullptr"), *FString(__FUNCTION__))
// 		return;
// 	}
// 	if (!FlashlightIcon_RED)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightIcon_RED is nullptr"), *FString(__FUNCTION__))
// 		return;
// 	}
// 	if (!FlashlightIcon_GREEN)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightIcon_GREEN is nullptr"), *FString(__FUNCTION__))
// 		return;
// 	}
// 	if (!FlashlightIcon_BLUE)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightIcon_BLUE is nullptr"), *FString(__FUNCTION__))
// 		return;
// 	}
// #pragma endregion
//
// 	OutlineIcon(FlashlightIcon_OFF, false);
// 	OutlineIcon(FlashlightIcon_WHITE, false);
// 	OutlineIcon(FlashlightIcon_RED, false);
// 	OutlineIcon(FlashlightIcon_GREEN, false);
// 	OutlineIcon(FlashlightIcon_BLUE, false);
//
// 	switch (UltraVioletColor)
// 	{
// 	case EUltraVioletColor::EVC_Off:
// 		OutlineIcon(FlashlightIcon_OFF);
// 		break;
// 	case EUltraVioletColor::EVC_White:
// 		OutlineIcon(FlashlightIcon_WHITE);
// 		break;
// 	case EUltraVioletColor::EVC_Red:
// 		OutlineIcon(FlashlightIcon_RED);
// 		break;
// 	case EUltraVioletColor::EVC_Green:
// 		OutlineIcon(FlashlightIcon_GREEN);
// 		break;
// 	case EUltraVioletColor::EVC_Blue:
// 		OutlineIcon(FlashlightIcon_BLUE);
// 		break;
// 	}
// }

void UERFlashlightWidget::OutlineIcon(UImage* Icon, const bool bOutline) const
{
#pragma region Nullchecks
	if (!FlashlightIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightIcon is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float Alpha{bOutline ? 1.f : 0.f};
	const FLinearColor OutlineColor{1.f, 0.7f, 0.f, Alpha};
	const FSlateColor SlateColor{OutlineColor};
	FSlateBrushOutlineSettings OutlineSettings{10.f, SlateColor, 3.f};
	OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	FSlateBrush SlateBrush;
	SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	SlateBrush.SetResourceObject(FlashlightIcon);
	SlateBrush.OutlineSettings = OutlineSettings;
	Icon->SetBrush(SlateBrush);
}
