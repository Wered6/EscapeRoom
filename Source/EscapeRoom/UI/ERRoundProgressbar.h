// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERRoundProgressbar.generated.h"

class UImage;

UCLASS()
class ESCAPEROOM_API UERRoundProgressbar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable, Category="ER")
	float GetPercent() const;
	UFUNCTION(BlueprintCallable, Category="ER")
	void SetPercent(const float InPercent) const;
	UFUNCTION(BlueprintCallable, Category="ER")
	void SetImageSize(const FVector2D InImageSize) const;
	UFUNCTION(BlueprintCallable, Category="ER")
	void SetBackgroundCircleOpacity(const float InOpacity) const;

private:
	UPROPERTY(EditAnywhere, Category="ER")
	float Percent{0.5f};
	UPROPERTY(EditAnywhere, Category="ER")
	FVector2D ImageSize{32.f, 32.f};
	UPROPERTY(EditAnywhere, Category="ER")
	float BackgroundCircleOpacity{0.2f};

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> RoundProgressBarMatDyn;
	UPROPERTY(EditDefaultsOnly, Category="ER")
	TObjectPtr<UMaterialInstance> RoundProgressBarMatInst;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> RoundProgressBarImage;
};
