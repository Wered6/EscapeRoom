// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypadHangman.h"
#include "EscapeRoom/Items/NonInteractables/TV/ERTV.h"


AERKeypadHangman::AERKeypadHangman()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AERKeypadHangman::BeginPlay()
{
	Super::BeginPlay();

#pragma region Nullchecks
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TV is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TV->OnCorrectHangmanPassword.BindUObject(this, &AERKeypadHangman::ExitAndDisableInteraction);
	OnFinishProcessing.BindUObject(this, &AERKeypadHangman::SendSignPasswordToTV);
}

void AERKeypadHangman::SendSignPasswordToTV()
{
	const TCHAR TempChar{Sign};
	const bool CorrectSign{TV->EnterSignToHangman(FString(1, &TempChar))};
	// Reset Sign
	Sign = 0b00000000;

	LedFlash(CorrectSign ? ELedColor::Green : ELedColor::Red, LedLongFlashTime);
}

void AERKeypadHangman::ButtonPressed()
{
	Super::ButtonPressed();

	if (SelectedButton.Name == EKeypadButtonName::OK)
	{
		// Limit between a-z A-Z
		if (Sign < 65 || (Sign > 90 && Sign < 96) || Sign > 122)
		{
			// 0b00111111 = '?' sign
			Sign = 0b00111111;
		}
	}
	else if (SelectedButton.Name == EKeypadButtonName::DEL)
	{
		Sign >>= 1;
	}
	// Other buttons (0-9)
	else
	{
		Sign <<= 1;
		Sign |= SelectedButton.Value;
	}
}

void AERKeypadHangman::ExitAndDisableInteraction()
{
	ExitKeypadMode();
	SetCanInteract(false);
}
