// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERUnlockInterface.generated.h"

UINTERFACE()
class UERUnlockInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Remember to use call to parent in blueprint if u want functionality from C++ and blueprints
 */
class IERUnlockInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Unlock")
	void Unlock();
};
