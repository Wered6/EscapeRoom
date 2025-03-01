// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypadConverter.h"
#include "EscapeRoom/Items/NonInteractables/TV/ERTV.h"


AERKeypadConverter::AERKeypadConverter()
{
	PrimaryActorTick.bCanEverTick = false;

	bProcessing = false;
}

void AERKeypadConverter::BeginPlay()
{
	Super::BeginPlay();

	OnFinishProcessing.BindUObject(this, &AERKeypadConverter::Convert);
}

void AERKeypadConverter::ButtonPressed()
{
#pragma region Nullchecks
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TV is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	if (SelectedButton.Name == EKeypadButtonName::OK)
	{
		if (!TV->NextRGBField())
		{
			bProcessing = true;
		}
	}
	else if (SelectedButton.Name == EKeypadButtonName::DEL)
	{
	}
	else
	{
		TV->SendNumberToConverter(SelectedButton.Value);
	}

	Super::ButtonPressed();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERKeypadConverter::Convert()
{
#pragma region Nullchecks
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TV is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TV->ConvertRGBToHSV();
	TV->ResetConverter();

	bProcessing = false;
}
