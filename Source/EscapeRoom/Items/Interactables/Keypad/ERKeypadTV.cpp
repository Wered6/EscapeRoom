// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypadTV.h"
#include "EscapeRoom/Items/NonInteractables/TV/ERTV.h"


AERKeypadTV::AERKeypadTV()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKeypadTV::BeginPlay()
{
	Super::BeginPlay();

#pragma region Nullchecks
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TV is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TV->OnCorrectPassword.BindUObject(this, &AERKeypadTV::ExitAndDisableInteraction);
	OnFinishProcessing.BindUObject(this, &AERKeypadTV::SendSignPasswordToTV);
}

void AERKeypadTV::KeypadButtonPressed_Implementation()
{
#pragma region Nullchecks
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TV is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Super::KeypadButtonPressed_Implementation();

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
		Sign <<= 1;
		Sign |= SelectedButton.Value;
		break;
	case EKeypadButtonValue::DEL:
		Sign >>= 1;
		break;
	case EKeypadButtonValue::OK:
		// Limit between a-z A-Z
		if (Sign < 65 || (Sign > 90 && Sign < 96) || Sign > 122)
		{
			// 0b00111111 = '?' sign
			Sign = 0b00111111;
		}
		break;
	}
}

void AERKeypadTV::SendSignPasswordToTV()
{
	const TCHAR TempChar{Sign};
	const bool CorrectSign{TV->EnterSignToPassword(FString(1, &TempChar))};
	// Reset Sign
	Sign = 0b00000000;

	LedFlash(CorrectSign ? ELedColor::Green : ELedColor::Red, LedLongFlashTime);
}

void AERKeypadTV::ExitAndDisableInteraction() const
{
	ExitKeypadMode();
	DisableInteraction();
}
