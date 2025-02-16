// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTVConverterScreenWidget.h"
#include "ERTVScreenSignWidget.h"

void UERTVConverterScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RGBArray.Add(RedValue);
	RGBArray.Add(GreenValue);
	RGBArray.Add(BlueValue);
}

void UERTVConverterScreenWidget::UpdateCurrentRGBArrayElement(const uint8 Number)
{
	if (CurrentTempNumberLen < MaxTempNumberLen)
	{
		CurrentTempNumberLen++;
	}
	else
	{
		TempNumber = TempNumber.RightChop(1);
	}
	TempNumber += FString::FromInt(Number);

	RGBArray[RGBArrayIndex]->UpdateText(TempNumber);
}

bool UERTVConverterScreenWidget::NextRGBField()
{
	RGBArray[RGBArrayIndex]->StopBlinkAnimation();
	if (RGBArrayIndex < 2)
	{
		CurrentTempNumberLen = 0;
		TempNumber.Empty();
		RGBArrayIndex++;
		RGBArray[RGBArrayIndex]->PlayBlinkAnimation();

		return true;
	}

	return false;
}

void UERTVConverterScreenWidget::Convert() const
{
	const FString RedString{RedValue->GetText().ToString()};
	const FString GreenString{GreenValue->GetText().ToString()};
	const FString BlueString{BlueValue->GetText().ToString()};
	const FLinearColor RGBColor{FCString::Atof(*RedString) / 255, FCString::Atof(*GreenString) / 255, FCString::Atof(*BlueString) / 255};
	const FLinearColor HSVColor{RGBColor.LinearRGBToHSV()};

	HSVHue->UpdateText(FString::FromInt(HSVColor.R));
	HSVSaturation->UpdateText(FString::FromInt(HSVColor.G * 100));
	HSVValue->UpdateText(FString::FromInt(HSVColor.B * 100));
}

void UERTVConverterScreenWidget::ResetRGBArrayIndex()
{
	RGBArrayIndex = 0;
}
