#include "ERInteractIconWidget.h"
#include "ERInteractInterface.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "EscapeRoom/UI/ERRoundProgressbar.h"


void UERInteractIconWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

#pragma region Nullchecks
	if (!IconSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|IconSwitcher is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!CollectIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|CollectIcon is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!OpenIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|OpenIcon is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!UseIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|UseIcon is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!UnlockIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|UnlockIcon is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressbar is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	switch (InteractCategory)
	{
	case EERInteractCategory::Use:
		IconSwitcher->SetActiveWidget(UseIcon);
		break;
	case EERInteractCategory::Collect:
		IconSwitcher->SetActiveWidget(CollectIcon);
		break;
	case EERInteractCategory::Open:
		IconSwitcher->SetActiveWidget(OpenIcon);
		break;
	case EERInteractCategory::Unlock:
		IconSwitcher->SetActiveWidget(UnlockIcon);
		break;
	}

	switch (InteractType)
	{
	case EERInteractType::Press:
		ProgressCircle->SetVisibility(ESlateVisibility::Collapsed);
		IconSwitcher->SetRenderOpacity(1.f);
		break;
	case EERInteractType::Hold:
		ProgressCircle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SetIconOpacity(InitialIconOpacity);
		SetProgressCircleOpacity(InitialProgressCircleOpacity);
		SetProgressCircleSize(ProgressCircleSize);
		SetProgressCirclePercent(0.f);
		break;
	}

	SetIconSize(IconSize);
}

void UERInteractIconWidget::Init(const EERInteractCategory NewInteractCategory,
                                 const EERInteractType NewInteractType,
                                 const float NewMinimalIconOpacity,
                                 const float NewInitialIconOpacity,
                                 const FVector2D NewIconSize,
                                 const float NewMinimalProgressCircleOpacity,
                                 const float NewInitialProgressCircleOpacity,
                                 const FVector2D NewProgressCircleSize)
{
	InteractCategory = NewInteractCategory;
	InteractType = NewInteractType;
	MinimalIconOpacity = NewMinimalIconOpacity;
	InitialIconOpacity = NewInitialIconOpacity;
	IconSize = NewIconSize;
	MinimalProgressCircleOpacity = NewMinimalProgressCircleOpacity;
	InitialProgressCircleOpacity = NewInitialProgressCircleOpacity;
	ProgressCircleSize = NewProgressCircleSize;
}

void UERInteractIconWidget::SetIconOpacity(const float Opacity) const
{
#pragma region Nullchecks
	if (!IconSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|IconSwitcher is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float LerpedOpacity{FMath::Lerp(MinimalIconOpacity, 1.f, Opacity)};
	IconSwitcher->SetRenderOpacity(LerpedOpacity);
}

void UERInteractIconWidget::SetIconSize(const FVector2D Size) const
{
#pragma region Nullchecks
	if (!IconSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|IconSwitcher is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	for (UWidget* Icon : IconSwitcher->GetAllChildren())
	{
		if (UImage* ImageIcon{Cast<UImage>(Icon)})
		{
			ImageIcon->SetDesiredSizeOverride(Size);
		}
	}
}

void UERInteractIconWidget::SetProgressCircleOpacity(const float Opacity) const
{
#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float LerpedOpacity{FMath::Lerp(MinimalProgressCircleOpacity, 1.f, Opacity)};
	ProgressCircle->SetOpacity(LerpedOpacity);
}

void UERInteractIconWidget::SetProgressCircleSize(const FVector2D Size) const
{
#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircle->SetImageSize(Size);
}

void UERInteractIconWidget::SetProgressCirclePercent(const float Percent) const
{
#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ProgressCircle->SetPercent(Percent);
}

void UERInteractIconWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressbar is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// decrease progress and opacity when not holding during 'Hold' interaction.
	if (InteractType == EERInteractType::Hold && !bIsHolding && ProgressCircle->GetPercent() > 0.f)
	{
		SetProgressCircleOpacity(ProgressCircle->GetOpacity() - InDeltaTime);
		ProgressCircle->SetPercent(ProgressCircle->GetPercent() - InDeltaTime);
		SetIconOpacity(ProgressCircle->GetOpacity() - InDeltaTime);
	}
}
