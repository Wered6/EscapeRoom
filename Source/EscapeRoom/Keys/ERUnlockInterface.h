// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERUnlockInterface.generated.h"

UINTERFACE(MinimalAPI)
class UERUnlockInterface : public UInterface
{
	GENERATED_BODY()
};

class IERUnlockInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER")
	void Unlock();
};
