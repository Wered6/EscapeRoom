// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERTVScreenWidget.generated.h"

class AERTV;
class UCanvasPanel;
class UERTVScreenSignWidget;
class UHorizontalBox;

DECLARE_DELEGATE()

UCLASS()
class ESCAPEROOM_API UERTVScreenWidget : public UUserWidget
{
	GENERATED_BODY()

	friend AERTV;

public:
	virtual void NativePreConstruct() override;

	bool EnterSignToPassword(const FString& Sign);

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> BravoWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UHorizontalBox> PasswordHBox;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UERTVScreenSignWidget> EnteredSign;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> FirstPanel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> SecondPanel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> ThirdPanel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> FourthPanel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> FifthPanel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> SixthPanel;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ER", meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UCanvasPanel> SeventhPanel;

	UPROPERTY(VisibleAnywhere, Category="ER")
	FString Password{};
	UPROPERTY(VisibleAnywhere, Category="ER")
	FString UserPassword;

	UPROPERTY(VisibleAnywhere, Category="ER")
	TArray<UCanvasPanel*> HangmanPanelsArray;
	UPROPERTY(VisibleAnywhere, Category="ER")
	uint8 HangmanPanelsArrayIndex;

	UPROPERTY(EditDefaultsOnly, Category="ER")
	TSubclassOf<UERTVScreenSignWidget> TVScreenSignWidgetClass;
};
