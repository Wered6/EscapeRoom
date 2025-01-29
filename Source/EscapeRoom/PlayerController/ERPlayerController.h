// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ERPlayerController.generated.h"

enum class EUltraVioletColor : uint8;
class UERFlashlightWidget;

UCLASS()
class ESCAPEROOM_API AERPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AddToViewportFlashlightWidget() const;
	void OutlineUltraVioletColor(const EUltraVioletColor UltraVioletColor) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UERFlashlightWidget> FlashlightWidgetClass;

	UPROPERTY()
	TObjectPtr<UERFlashlightWidget> FlashlightWidget;
};
