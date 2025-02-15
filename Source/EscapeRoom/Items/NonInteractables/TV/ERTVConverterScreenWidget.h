// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERTVConverterScreenWidget.generated.h"

class UERTVScreenSignWidget;

UCLASS()
class ESCAPEROOM_API UERTVConverterScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Default", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> R;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Default", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> G;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Default", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> B;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Default", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> H;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Default", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> S;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER|Default", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> V;
};
