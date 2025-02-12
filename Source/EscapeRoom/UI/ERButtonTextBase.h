// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERButtonTextBase.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonTextClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonTextPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonTextReleased);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonTextHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonTextUnhovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonTextHold, float, DeltaSeconds);

UCLASS()
class ESCAPEROOM_API UERButtonTextBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category="ER|Button")
	FOnButtonTextClicked OnClicked;
	UPROPERTY(BlueprintAssignable, Category="ER|Button")
	FOnButtonTextPressed OnPressed;
	UPROPERTY(BlueprintAssignable, Category="ER|Button")
	FOnButtonTextReleased OnReleased;
	UPROPERTY(BlueprintAssignable, Category="ER|Button")
	FOnButtonTextHovered OnHovered;
	UPROPERTY(BlueprintAssignable, Category="ER|Button")
	FOnButtonTextUnhovered OnUnhovered;
	UPROPERTY(BlueprintAssignable, Category="ER|Button")
	FOnButtonTextHold OnHold;

private:
	UFUNCTION()
	void OnClickedHandle();
	UFUNCTION()
	void OnPressedHandle();
	UFUNCTION()
	void OnReleasedHandle();
	UFUNCTION()
	void OnHoveredHandle();
	UFUNCTION()
	void OnUnhoveredHandle();
	void OnHoldHandle(float DeltaSeconds);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Hold")
	float HoldThreshold{0.f};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Hold", DisplayName="Hold Interval")
	float DefaultHoldInterval{0.f};
	float HoldInterval{0.f};
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Hold")
	float HoldIntervalReduction{0.f};
	float HoldDuration{0.f};
	bool bIsHolding{};

#pragma region Button

public:
	UFUNCTION(BlueprintCallable, Category="ER|Button")
	void SetBStyle(const FButtonStyle InStyle) const;
	UFUNCTION(BlueprintCallable, Category="ER|Button")
	void SetBColorAndOpacity(const FLinearColor InColorAndOpacity) const;
	UFUNCTION(BlueprintCallable, Category="ER|Button")
	void SetBBackgroundColor(const FLinearColor InBackgroundColor) const;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Button|Appearance", DisplayName="Style")
	FButtonStyle BStyle;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Button|Appearance", DisplayName="Color and Opacity")
	FLinearColor BColorAndOpacity;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Button|Appearance", DisplayName="Background Color")
	FLinearColor BBackgroundColor;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UButton> Button;

#pragma endregion

#pragma region Text

public:
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBText(const FText InText) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBColorAndOpacity(const FSlateColor InColorAndOpacity) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBFont(const FSlateFontInfo InFontInfo) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBStrikeBrush(const FSlateBrush InStrikeBrush) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBShadowOffset(const FVector2D InShadowOffset) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBShadowColorAndOpacity(const FLinearColor InShadowColorAndOpacity) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBTextTransformPolicy(const ETextTransformPolicy InTransformPolicy) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBJustification(const ETextJustify::Type InJustification) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBAutoWrapText(const bool InAutoTextWrap) const;
	UFUNCTION(BlueprintCallable, Category="ER|Text")
	void SetTBWrapTextAt(const float InWrapTextAt) const;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Content", DisplayName="Text")
	FText TBText;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Font")
	FSlateFontInfo TBFont;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Color and Opacity")
	FSlateColor TBColorAndOpacity;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Strike Brush")
	FSlateBrush TBStrikeBrush;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Shadow Offset")
	FVector2D TBShadowOffset;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Shadow Color")
	FLinearColor TBShadowColor;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Transform Policy")
	ETextTransformPolicy TBTransformPolicy;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Appearance", DisplayName="Justification")
	TEnumAsByte<ETextJustify::Type> TBJustification;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Wrapping", DisplayName="Auto Wrap Text")
	bool TBAutoTextWrap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn=true, AllowPrivateAccess=true), Category="ER|Text|Wrapping", DisplayName="Auto Wrap Text")
	float TBWrapTextAt;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true))
	TObjectPtr<UTextBlock> TextBlock;

#pragma endregion
};
