// Fill out your copyright notice in the Description page of Project Settings.


#include "ERRoundProgressbar.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UERRoundProgressbar::NativePreConstruct()
{
	Super::NativePreConstruct();

#pragma region Nullchecks
	if (!RoundProgressBarMatInst)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressBarMaterialInstance is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!RoundProgressBarImage)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressbarImage is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	RoundProgressBarMatDyn = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, RoundProgressBarMatInst);
	RoundProgressBarImage->SetBrushFromMaterial(RoundProgressBarMatDyn);
	SetPercent(Percent);
	SetBackgroundCircleOpacity(BackgroundCircleOpacity);
	SetImageSize(ImageSize);
}

float UERRoundProgressbar::GetPercent() const
{
#pragma region Nullchecks
	if (!RoundProgressBarMatDyn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressBarMatDyn is nullptr"), *FString(__FUNCTION__))
		return 0.f;
	}
#pragma endregion

	float OutPercent;
	RoundProgressBarMatDyn->GetScalarParameterValue(FName("Percent"), OutPercent);

	return OutPercent;
}

void UERRoundProgressbar::SetPercent(const float InPercent) const
{
#pragma region Nullchecks
	if (!RoundProgressBarMatDyn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressBarMatInst is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	RoundProgressBarMatDyn->SetScalarParameterValue(FName("Percent"), InPercent);
}

void UERRoundProgressbar::SetImageSize(const FVector2D InImageSize) const
{
#pragma region Nullchecks
	if (!RoundProgressBarImage)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressBarImage is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	RoundProgressBarImage->SetDesiredSizeOverride(InImageSize);
}

void UERRoundProgressbar::SetBackgroundCircleOpacity(const float InOpacity) const
{
#pragma region Nullchecks
	if (!RoundProgressBarMatDyn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressBarMatDyn is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	RoundProgressBarMatDyn->SetScalarParameterValue(FName("BackgroundCircleOpacity"), InOpacity);
}
