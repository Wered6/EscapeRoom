// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERTVConverterScreenWidget.generated.h"

class AERTV;
class UERTVScreenSignWidget;

UCLASS()
class ESCAPEROOM_API UERTVConverterScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void UpdateCurrentRGBArrayElement(const uint8 Number);
	/**
	 * @return Return if there is next RGB field
	 */
	bool NextRGBField();
	void Convert() const;
	void ResetRGBArrayIndex();

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|RGB", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> RedValue;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|RGB", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> GreenValue;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|RGB", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> BlueValue;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|HSV", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> HSVHue;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|HSV", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> HSVSaturation;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|HSV", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> HSVValue;

	uint8 CurrentTempNumberLen{};
	uint8 MaxTempNumberLen{3};
	FString TempNumber{};

	UPROPERTY(VisibleAnywhere, Category="ER|RGB")
	TArray<TObjectPtr<UERTVScreenSignWidget>> RGBArray;
	UPROPERTY(VisibleAnywhere, Category="ER|RGB")
	uint8 RGBArrayIndex{};
};
