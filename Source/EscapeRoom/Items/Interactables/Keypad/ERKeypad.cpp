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

	OnFinishProcessing.BindUObject(this, &AERKeypad::CheckPassword);
}

void AERKeypad::ButtonPressed()
{
	Super::ButtonPressed();

	if (SelectedButton.Name == EKeypadButtonName::OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("UserPassword: %s"), *UserPassword)
		// In parent here is OnFinishProcessing, if you want to do something after OK, bind to OnFinishProcessing
	}
	else if (SelectedButton.Name == EKeypadButtonName::DEL)
	{
		if (!UserPassword.IsEmpty())
		{
			UserPassword = UserPassword.LeftChop(1);
		}
	}
	// Other buttons (0-9)
	else
	{
		UserPassword = UserPassword + FString::FromInt(SelectedButton.Value);
	}
}

void AERKeypad::CheckPassword()
{
	if (Password == UserPassword)
	{
		KeyComponent->UnlockLockedItems();
		LedFlash(ELedColor::Green, LedLongFlashTime);
		ExitKeypadMode();
		DisableInteraction();

		if (OnCorrectPassword.IsBound())
		{
			OnCorrectPassword.Execute();
		}
	}
	else
	{
		LedFlash(ELedColor::Red, LedLongFlashTime);
		UserPassword.Empty();

		if (OnWrongPassword.IsBound())
		{
			OnWrongPassword.Execute();
		}
	}
}
