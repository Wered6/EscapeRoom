// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERInteractIconWidget.generated.h"

class UImage;
class UWidgetSwitcher;
class UERRoundProgressbar;
enum class EERInteractType : uint8;
enum class EERInteractCategory : uint8;

UCLASS()
class ESCAPEROOM_API UERInteractIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void Init(const EERInteractCategory NewInteractCategory,
	          const EERInteractType NewInteractType,
	          const float NewMinimalIconOpacity,
	          const float NewInitialIconOpacity,
	          const FVector2D NewIconSize,
	          const float NewMinimalProgressCircleOpacity,
	          const float NewInitialProgressCircleOpacity,
	          const FVector2D NewProgressCircleSize,
	          const float NewProgressCirclePercent);

	void SetIconOpacity(const float Opacity) const;
	void SetIconSize(const FVector2D Size) const;

	void SetProgressCircleOpacity(const float Opacity) const;
	void SetProgressCircleSize(const FVector2D Size) const;
	void SetProgressCirclePercent(const float Percent) const;

	FORCEINLINE void SetIsHolding(const bool bNewIsHolding)
	{
		bIsHolding = bNewIsHolding;
	}

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	EERInteractCategory InteractCategory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	EERInteractType InteractType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1"), Category="ER|Interact")
	float MinimalIconOpacity{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1"), Category="ER|Interact")
	float InitialIconOpacity{0.3f};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	FVector2D IconSize{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalProgressCircleOpacity{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float InitialProgressCircleOpacity{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	FVector2D ProgressCircleSize{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float InitialProgressCirclePercent{};

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	bool bIsHolding{};

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UERRoundProgressbar> ProgressCircle;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UWidgetSwitcher> IconSwitcher;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UImage> CollectIcon;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UImage> OpenIcon;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UImage> UseIcon;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UImage> UnlockIcon;
};
