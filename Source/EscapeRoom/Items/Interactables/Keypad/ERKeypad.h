// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadBase.h"
#include "ERKeypad.generated.h"

class UERKeyComponent;

UCLASS()
class ESCAPEROOM_API AERKeypad : public AERKeypadBase
{
	GENERATED_BODY()

public:
	AERKeypad();

protected:
	virtual void BeginPlay() override;

public:
	/**
	 * Overriding KeypadAcceptButtonPressed function from ERKeypadInterface
	 */
	virtual void KeypadAcceptButtonPressed_Implementation() override;

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
