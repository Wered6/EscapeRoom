// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERInteractInterface.generated.h"

UINTERFACE()
class UERInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Remember to use call to parent in blueprint if u want functionality from C++ and blueprints
 */
class IERInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	void InteractStart(AActor* OtherInstigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	void DisplayInteractionUI(const bool bShowInteract);
};
