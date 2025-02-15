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

void AERKeypadConverter::KeypadButtonPressed_Implementation()
{
#pragma region Nullchecks
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TV is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	switch (SelectedButton.KeypadButtonValue)
	{
	case EKeypadButtonValue::Zero:
	case EKeypadButtonValue::One:
	case EKeypadButtonValue::Two:
	case EKeypadButtonValue::Three:
	case EKeypadButtonValue::Four:
	case EKeypadButtonValue::Five:
	case EKeypadButtonValue::Six:
	case EKeypadButtonValue::Seven:
	case EKeypadButtonValue::Eight:
	case EKeypadButtonValue::Nine:
		TV->SendNumberToConverter(SelectedButton.Value);
		break;
	case EKeypadButtonValue::DEL:
		break;
	case EKeypadButtonValue::OK:
		if (!TV->NextRGBField())
		{
			bProcessing = true;
		}
		break;
	}

	Super::KeypadButtonPressed_Implementation();
}

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
}
