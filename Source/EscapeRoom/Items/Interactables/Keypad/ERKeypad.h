// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadBase.h"
#include "ERKeypad.generated.h"

class UERKeyComponent;

DECLARE_DELEGATE(FOnCorrectPassword)
DECLARE_DELEGATE(FOnWrongPassword)

UCLASS()
class ESCAPEROOM_API AERKeypad : public AERKeypadBase
{
	GENERATED_BODY()

public:
	AERKeypad();

protected:
	virtual void BeginPlay() override;

public:
	FOnCorrectPassword OnCorrectPassword;
	FOnWrongPassword OnWrongPassword;

protected:
	virtual void ButtonPressed() override;

private:
	void CheckPassword();

	UPROPERTY(EditAnywhere, Category="ER|Keypad|Password")
	FString Password;
	UPROPERTY(VisibleAnywhere, Category="ER|Keypad|Password")
	FString UserPassword;

	UPROPERTY(VisibleAnywhere, Category="ER|Key")
	TObjectPtr<UERKeyComponent> KeyComponent;

	// TODO try to combine meshes and textures to lower the size
};
