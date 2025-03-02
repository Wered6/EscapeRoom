// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ERPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class ESCAPEROOM_API AERPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

#pragma region Input

protected:
	virtual void SetupInputComponent() override;

	/**
	 * Bind to MenuPause
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void TriggerMenuPause();

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Menu")
	TObjectPtr<UInputMappingContext> MenuMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="ER|Input|Menu")
	TObjectPtr<UInputAction> MenuPauseAction;

#pragma endregion
};
