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

void AERKeypad::KeypadButtonPressed_Implementation()
{
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
		UserPassword = UserPassword + FString::FromInt(SelectedButton.Value);
		break;
	case EKeypadButtonValue::DEL:
		if (!UserPassword.IsEmpty())
		{
			UserPassword = UserPassword.LeftChop(1);
		}
		break;
	case EKeypadButtonValue::OK:
		UE_LOG(LogTemp, Warning, TEXT("UserPassword: %s"), *UserPassword)
	// In parent here is StartLedBlinking, if you want to do something after OK, bind to OnEndLedBlinking
		break;
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
	}
	else
	{
		LedFlash(ELedColor::Red, LedLongFlashTime);
		UserPassword.Empty();
	}
}
