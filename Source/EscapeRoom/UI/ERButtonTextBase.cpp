// Fill out your copyright notice in the Description page of Project Settings.


#include "ERButtonTextBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UERButtonTextBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetTBText(TBText);
	SetTBColorAndOpacity(TBColorAndOpacity);
	SetTBFont(TBFont);
	SetTBStrikeBrush(TBStrikeBrush);
	SetTBShadowOffset(TBShadowOffset);
	SetTBShadowColorAndOpacity(TBShadowColor);
	SetTBTextTransformPolicy(TBTransformPolicy);
	SetTBJustification(TBJustification);
	SetTBAutoWrapText(TBAutoTextWrap);
	SetTBWrapTextAt(TBWrapTextAt);

	SetBStyle(BStyle);
	SetBColorAndOpacity(BColorAndOpacity);
	SetBBackgroundColor(BBackgroundColor);

	HoldInterval = DefaultHoldInterval;
}

void UERButtonTextBase::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UERButtonTextBase::OnClickedHandle);
	Button->OnPressed.AddDynamic(this, &UERButtonTextBase::OnPressedHandle);
	Button->OnReleased.AddDynamic(this, &UERButtonTextBase::OnReleasedHandle);
	Button->OnHovered.AddDynamic(this, &UERButtonTextBase::OnHoveredHandle);
	Button->OnUnhovered.AddDynamic(this, &UERButtonTextBase::OnUnhoveredHandle);
}

void UERButtonTextBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	OnHoldHandle(InDeltaTime);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERButtonTextBase::OnClickedHandle()
{
	OnClicked.Broadcast();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERButtonTextBase::OnPressedHandle()
{
	OnPressed.Broadcast();
	bIsHolding = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERButtonTextBase::OnReleasedHandle()
{
	OnReleased.Broadcast();
	bIsHolding = false;
	HoldDuration = 0.f;
	HoldInterval = DefaultHoldInterval;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERButtonTextBase::OnHoveredHandle()
{
	OnHovered.Broadcast();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UERButtonTextBase::OnUnhoveredHandle()
{
	OnUnhovered.Broadcast();
}

void UERButtonTextBase::OnHoldHandle(const float DeltaSeconds)
{
	if (bIsHolding)
	{
		HoldDuration += DeltaSeconds;
		if (HoldDuration >= HoldThreshold && HoldDuration - HoldThreshold >= HoldInterval)
		{
			OnHold.Broadcast(DeltaSeconds);
			HoldDuration -= HoldInterval;
			HoldInterval = FMath::Clamp(HoldInterval - HoldIntervalReduction, 0.f, DefaultHoldInterval);
		}
	}
}

void UERButtonTextBase::SetBStyle(const FButtonStyle InStyle) const
{
	Button->SetStyle(InStyle);
}

void UERButtonTextBase::SetBColorAndOpacity(const FLinearColor InColorAndOpacity) const
{
	Button->SetColorAndOpacity(InColorAndOpacity);
}

void UERButtonTextBase::SetBBackgroundColor(const FLinearColor InBackgroundColor) const
{
	Button->SetBackgroundColor(InBackgroundColor);
}

void UERButtonTextBase::SetTBText(const FText InText) const
{
	TextBlock->SetText(InText);
}

void UERButtonTextBase::SetTBColorAndOpacity(const FSlateColor InColorAndOpacity) const
{
	TextBlock->SetColorAndOpacity(InColorAndOpacity);
}

void UERButtonTextBase::SetTBFont(const FSlateFontInfo InFontInfo) const
{
	TextBlock->SetFont(InFontInfo);
}

void UERButtonTextBase::SetTBStrikeBrush(const FSlateBrush InStrikeBrush) const
{
	TextBlock->SetStrikeBrush(InStrikeBrush);
}

void UERButtonTextBase::SetTBShadowOffset(const FVector2D InShadowOffset) const
{
	TextBlock->SetShadowOffset(InShadowOffset);
}

void UERButtonTextBase::SetTBShadowColorAndOpacity(const FLinearColor InShadowColorAndOpacity) const
{
	TextBlock->SetShadowColorAndOpacity(InShadowColorAndOpacity);
}

void UERButtonTextBase::SetTBTextTransformPolicy(const ETextTransformPolicy InTransformPolicy) const
{
	TextBlock->SetTextTransformPolicy(InTransformPolicy);
}

void UERButtonTextBase::SetTBJustification(const ETextJustify::Type InJustification) const
{
	TextBlock->SetJustification(InJustification);
}

void UERButtonTextBase::SetTBAutoWrapText(const bool InAutoTextWrap) const
{
	TextBlock->SetAutoWrapText(InAutoTextWrap);
}

void UERButtonTextBase::SetTBWrapTextAt(const float InWrapTextAt) const
{
	TextBlock->SetWrapTextAt(InWrapTextAt);
}
