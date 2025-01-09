// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPlayerController.h"
#include "EscapeRoom/HUD/FlashlightWidget.h"
#include "EscapeRoom/Items/Interactables/Flashlight/ERFlashlight.h"

void AERPlayerController::AddToViewportFlashlightWidget() const
{
#pragma region Nullchecks
	if (!FlashlightWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	FlashlightWidget->AddToViewport();
	FlashlightWidget->OutlineUltraVioletColor(EUltraVioletColor::EVC_Off);
}

void AERPlayerController::OutlineUltraVioletColor(const EUltraVioletColor UltraVioletColor) const
{
#pragma region Nullchecks
	if (!FlashlightWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	FlashlightWidget->OutlineUltraVioletColor(UltraVioletColor);
}

void AERPlayerController::BeginPlay()
{
	Super::BeginPlay();

#pragma region Nullchecks
	if (!FlashlightWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightWidgetClass is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	FlashlightWidget = CreateWidget<UFlashlightWidget>(this, FlashlightWidgetClass);
}
