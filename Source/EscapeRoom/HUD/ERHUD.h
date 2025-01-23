// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ERHUD.generated.h"

UCLASS()
class ESCAPEROOM_API AERHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void DrawHUD() override;

	FORCEINLINE void SetIndicatorVisibility(const bool bVisible)
	{
		bIndicatorVisibility = bVisible;
	}

private:
	void DrawDotCenter();

	UPROPERTY(EditDefaultsOnly, Category="ER|Indicator")
	TObjectPtr<UTexture2D> DotCenter;

	UPROPERTY(VisibleAnywhere, Category="ER|Indicator")
	bool bIndicatorVisibility{true};
};
