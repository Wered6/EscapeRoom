// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypad.h"
#include "EscapeRoom/Components/ERKeyComponent.h"


AERKeypad::AERKeypad()
{
	KeyComponent = CreateDefaultSubobject<UERKeyComponent>(TEXT("KeyComponent"));
}

void AERKeypad::BeginPlay()
{
	Super::BeginPlay();

	OnEndLedBlinking.BindUObject(this, &AERKeypad::CheckPassword);
}

void AERKeypad::KeypadButtonPressed_Implementation()
{
	Super::KeypadButtonPressed_Implementation();

	// All buttons except DEL and OK
	if (SelectedButton.Value < 10)
	{
		UserPassword = UserPassword + FString::FromInt(SelectedButton.Value);
	}
	// DEL/OK
	else
	{
		// If DEL
		if (SelectedButton.Value == 10)
		{
			if (!UserPassword.IsEmpty())
			{
				UserPassword = UserPassword.LeftChop(1);
			}
		}
		// If OK
		else if (SelectedButton.Value == 20)
		{
			UE_LOG(LogTemp, Warning, TEXT("UserPassword: %s"), *UserPassword)
			// In parent here is StartLedBlinking, if you want to do something after OK, bind to OnEndLedBlinking
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonPressed"))
	// TODO add sound for clicking
}

void AERKeypad::CheckPassword()
{
	if (Password == UserPassword)
	{
		KeyComponent->UnlockLockedItems();
		LedFlash(ELedColor::Green, LedLongFlashTime);
		ExitKeypadMode();
		DisableInteraction();
	}
	else
	{
		LedFlash(ELedColor::Red, LedLongFlashTime);
		UserPassword.Empty();
	}
}
