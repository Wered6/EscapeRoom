// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERKeypadInteface.generated.h"

UINTERFACE(Blueprintable)
class UERKeypadInterface : public UInterface
{
	GENERATED_BODY()
};

class IERKeypadInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void KeypadMove(const FVector2D& MovementVector);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void KeypadAcceptButtonPressed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void KeypadAcceptButtonReleased();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void KeypadExit();
};
