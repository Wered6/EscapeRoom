// Fill out your copyright notice in the Description page of Project Settings.


#include "ERProgressCircle.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UERProgressCircle::NativePreConstruct()
{
	Super::NativePreConstruct();

#pragma region Nullchecks
	if (!ProgressCircleMatInst)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircleMatInst is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ProgressCircleImage)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircleImage is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircleMatDyn = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, ProgressCircleMatInst);
	ProgressCircleImage->SetBrushFromMaterial(ProgressCircleMatDyn);
	SetPercent(Percent);
	SetBackgroundCircleOpacity(BackgroundCircleOpacity);
	SetImageSize(ImageSize);
}

void UERProgressCircle::SetPercent(const float InPercent) const
{
#pragma region Nullchecks
	if (!ProgressCircleMatDyn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircleMatDyn is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircleMatDyn->SetScalarParameterValue(FName("Percent"), FMath::Clamp(InPercent, 0.f, 1.f));
}

void UERProgressCircle::SetOpacity(const float InOpacity) const
{
#pragma region Nullchecks
	if (!ProgressCircleMatDyn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircleMatDyn is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircleMatDyn->SetScalarParameterValue(FName("Opacity"), FMath::Clamp(InOpacity, 0.f, 1.f));
}

void UERProgressCircle::SetImageSize(const FVector2D InImageSize) const
{
#pragma region Nullchecks
	if (!ProgressCircleImage)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircleImage is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircleImage->SetDesiredSizeOverride(InImageSize);
}

void UERProgressCircle::SetBackgroundCircleOpacity(const float InOpacity) const
{
#pragma region Nullchecks
	if (!ProgressCircleMatDyn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircleMatDyn is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircleMatDyn->SetScalarParameterValue(FName("BackgroundCircleOpacity"), InOpacity);
}
