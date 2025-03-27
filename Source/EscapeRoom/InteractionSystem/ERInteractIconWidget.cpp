#include "ERInteractIconWidget.h"
#include "ERInteractInterface.h"
#include "ERProgressCircle.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"


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
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
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
		SetIconOpacity(1.f);
		UE_LOG(LogTemp, Warning, TEXT("Press"))
		break;
	case EERInteractType::Hold:
		ProgressCircle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SetIconOpacity(0.f);
		SetProgressCircleOpacity(0.f);
		SetProgressCirclePercent(0.f);
		SetProgressCircleSize(ProgressCircleSize);
		UE_LOG(LogTemp, Warning, TEXT("Hold"))
		break;
	}

	SetIconSize(IconSize);
}

void UERInteractIconWidget::Init(const EERInteractCategory NewInteractCategory,
                                 const EERInteractType NewInteractType,
                                 const float NewMinimalIconOpacity,
                                 const FVector2D NewIconSize,
                                 const float NewMinimalProgressCircleOpacity,
                                 const FVector2D NewProgressCircleSize)
{
	InteractCategory = NewInteractCategory;
	InteractType = NewInteractType;
	MinimalIconOpacity = NewMinimalIconOpacity;
	IconSize = NewIconSize;
	MinimalProgressCircleOpacity = NewMinimalProgressCircleOpacity;
	ProgressCircleSize = NewProgressCircleSize;
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

void UERInteractIconWidget::SetIconOpacity(const float Opacity)
{
#pragma region Nullchecks
	if (!IconSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|IconSwitcher is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float ClampedOpacity{FMath::Clamp(Opacity, 0.f, 1.f)};
	CurrentIconOpacity = FMath::Lerp(MinimalIconOpacity, 1.f, ClampedOpacity);

	IconSwitcher->SetRenderOpacity(CurrentIconOpacity);
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

void UERInteractIconWidget::SetProgressCircleOpacity(const float Opacity)
{
#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float ClampedOpacity{FMath::Clamp(Opacity, 0.f, 1.f)};
	CurrentProgressCircleOpacity = FMath::Lerp(MinimalProgressCircleOpacity, 1.f, ClampedOpacity);
	ProgressCircle->SetOpacity(CurrentProgressCircleOpacity);
}

void UERInteractIconWidget::SetProgressCirclePercent(const float Percent)
{
#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const float ClampedPercent{FMath::Clamp(Percent, 0.f, 1.f)};
	CurrentProgressCirclePercent = ClampedPercent;
	ProgressCircle->SetPercent(CurrentProgressCirclePercent);
}

void UERInteractIconWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

#pragma region Nullchecks
	if (!ProgressCircle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ProgressCircle is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Check if progress or opacity needs to be reduced
	const bool bNeedsReduction
	{
		CurrentIconOpacity > MinimalIconOpacity || CurrentProgressCircleOpacity > MinimalProgressCircleOpacity || CurrentProgressCirclePercent > 0.f
	};
	// Decrease progress and opacity when not holding and if interact type is hold.
	if (InteractType == EERInteractType::Hold && !bIsHolding && bNeedsReduction)
	{
		DecreaseIconOpacity(InDeltaTime);
		DecreaseProgressCircleOpacity(InDeltaTime);
		SetProgressCirclePercent(CurrentProgressCirclePercent - InDeltaTime);
	}
}

void UERInteractIconWidget::DecreaseIconOpacity(const float Value)
{
	CurrentIconOpacity -= Value;
	CurrentIconOpacity = FMath::Clamp(CurrentIconOpacity, MinimalIconOpacity, 1.f);
	IconSwitcher->SetRenderOpacity(CurrentIconOpacity);
}

void UERInteractIconWidget::DecreaseProgressCircleOpacity(const float Value)
{
	CurrentProgressCircleOpacity -= Value;
	CurrentProgressCircleOpacity = FMath::Clamp(CurrentProgressCircleOpacity, MinimalProgressCircleOpacity, 1.f);
	ProgressCircle->SetOpacity(CurrentProgressCircleOpacity);
}
