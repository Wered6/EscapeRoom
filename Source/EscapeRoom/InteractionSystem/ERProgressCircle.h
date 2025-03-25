// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERProgressCircle.generated.h"

class UImage;

UCLASS()
class ESCAPEROOM_API UERProgressCircle : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	/**
	 * Sets the percentage of the foreground circle.
	 */
	UFUNCTION(BlueprintCallable, Category="ER")
	void SetPercent(const float InPercent) const;

	/**
	 * Sets the opacity of the foreground circle.
	 */
	UFUNCTION(BlueprintCallable, Category="ER")
	void SetOpacity(const float InOpacity) const;

	UFUNCTION(BlueprintCallable, Category="ER")
	void SetImageSize(const FVector2D InImageSize) const;
	UFUNCTION(BlueprintCallable, Category="ER")
	void SetBackgroundCircleOpacity(const float InOpacity) const;

private:
	/**
	 * Percentage of the foreground circle.
	 */
	UPROPERTY(EditAnywhere, Category="ER")
	float Percent{0.5f};
	/**
	 * Opacity of the foreground circle.
	 */
	UPROPERTY(EditAnywhere, Category="ER")
	float Opacity{1.f};
	UPROPERTY(EditAnywhere, Category="ER")
	FVector2D ImageSize{32.f, 32.f};
	UPROPERTY(EditAnywhere, Category="ER")
	float BackgroundCircleOpacity{0.2f};

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> ProgressCircleMatDyn;
	UPROPERTY(EditDefaultsOnly, Category="ER")
	TObjectPtr<UMaterialInstance> ProgressCircleMatInst;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ProgressCircleImage;
};
