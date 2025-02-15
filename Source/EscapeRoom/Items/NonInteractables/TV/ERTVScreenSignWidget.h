// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ERTVScreenSignWidget.generated.h"

class UERTVConverterScreenWidget;
class UERTVScreenWidget;
class UTextBlock;

UCLASS()
class ESCAPEROOM_API UERTVScreenSignWidget : public UUserWidget
{
	GENERATED_BODY()

	friend UERTVScreenWidget;

public:
	virtual void NativePreConstruct() override;

	FText GetText() const
	{
		return Sign->GetText();
	}

	UFUNCTION(BlueprintCallable, Category="ER")
	void UpdateText(const FString NewText) const;
	UFUNCTION(BlueprintCallable, Category="ER")
	void UpdateFont(UObject* NewFontFamily, const float NewFontSize) const;

	UFUNCTION(BlueprintCallable, Category="ER")
	void PlayBlinkAnimation();
	UFUNCTION(BlueprintCallable, Category="ER")
	void StopBlinkAnimation();

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> Sign;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", Transient, meta=(BindWidgetAnim, AllowPrivateAccess=true))
	TObjectPtr<UWidgetAnimation> BlinkAnimation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	FString Text;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	TObjectPtr<UObject> FontFamily;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	float FontSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ER", meta=(ExposeOnSpawn=true, AllowPrivateAccess=true))
	bool bBlinkFromStart{false};
};
