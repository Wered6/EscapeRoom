#include "ERInteractIconWidget.h"
#include "ERRoundProgressbar.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"


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
	if (!RoundProgressbar)
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
		RoundProgressbar->SetVisibility(ESlateVisibility::Collapsed);
		IconSwitcher->SetRenderOpacity(1.f);
		break;
	case EERInteractType::Hold:
		RoundProgressbar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	}

	SetProgressbarPercent(InitialRoundProgressbarPercent);
	SetSize(RoundProgressbarSize, IconSize);
}

void UERInteractIconWidget::Init(const EERInteractCategory NewInteractCategory,
                                 const EERInteractType NewInteractType,
                                 const float NewRoundProgressbarPercent,
                                 const FVector2D NewRoundProgressbarSize,
                                 const FVector2D NewIconSize)
{
	InteractCategory = NewInteractCategory;
	InteractType = NewInteractType;
	InitialRoundProgressbarPercent = NewRoundProgressbarPercent;
	RoundProgressbarSize = NewRoundProgressbarSize;
	IconSize = NewIconSize;
}

void UERInteractIconWidget::SetProgressbarPercent(const float Percent) const
{
#pragma region Nullchecks
	if (!IconSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|IconSwitcher is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!RoundProgressbar)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressbar is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	IconSwitcher->SetRenderOpacity(FMath::Lerp(0.3, 1.f, Percent));
	RoundProgressbar->SetPercent(Percent);
}

void UERInteractIconWidget::SetSize(const FVector2D NewRoundProgressbarSize, const FVector2D NewIconSize) const
{
#pragma region Nullchecks
	if (!RoundProgressbar)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressbar is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!IconSwitcher)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|IconSwitcher is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	RoundProgressbar->SetImageSize(NewRoundProgressbarSize);

	for (UWidget* Icon : IconSwitcher->GetAllChildren())
	{
		UImage* ImageIcon{Cast<UImage>(Icon)};
		if (ImageIcon)
		{
			ImageIcon->SetDesiredSizeOverride(NewIconSize);
		}
	}
}

void UERInteractIconWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

#pragma region Nullchecks
	if (!RoundProgressbar)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RoundProgressbar is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	if (InteractType == EERInteractType::Hold && !bIsHolding && RoundProgressbar->GetPercent() > 0.f)
	{
		RoundProgressbar->SetPercent(RoundProgressbar->GetPercent() - InDeltaTime);
	}
}
