// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ERInteractIconWidget.generated.h"

class UImage;
class UWidgetSwitcher;
class UERProgressCircle;
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
	          const FVector2D NewIconSize,
	          const float NewMinimalProgressCircleOpacity,
	          const FVector2D NewProgressCircleSize);

	void SetIconSize(const FVector2D Size) const;
	/**
	 * Sets the opacity of the interaction icon by interpolating between the minimal and 1.f opacity.
	 * To decrease @see DecreaseIconOpacity
	 *
	 * @see MinimalIconOpacity
	 */
	void SetIconOpacity(const float Opacity);

	void SetProgressCircleSize(const FVector2D Size) const;
	/**
	 * Sets the opacity of the progress circle by interpolating between the minimal and 1.f opacity.
	 * To decrease @see DecreaseProgressCircleOpacity
	 *
	 * @see MinimalProgressCircleOpacity
	 */
	void SetProgressCircleOpacity(const float Opacity);
	/**
	 * Updates the progress circle's fill percentage.
	 *
	 * @param Percent Range: 0.f to 1.f.
	 */
	void SetProgressCirclePercent(const float Percent);

	FORCEINLINE void SetIsHolding(const bool bNewIsHolding)
	{
		bIsHolding = bNewIsHolding;
	}

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	/**
	 * Reduces the opacity of the interaction icon by a specified value.
	 */
	void DecreaseIconOpacity(const float Value);
	/**
	 * Reduces the opacity of the progress circle by the specified value.
	 *
	 */
	void DecreaseProgressCircleOpacity(const float Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	EERInteractCategory InteractCategory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	EERInteractType InteractType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	FVector2D IconSize{50.f, 50.f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalIconOpacity{0.3f};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	FVector2D ProgressCircleSize{100.f, 100.f};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalProgressCircleOpacity{0.f};

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	float CurrentIconOpacity{};
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	float CurrentProgressCircleOpacity{};
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	float CurrentProgressCirclePercent{};
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	bool bIsHolding{};

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UERProgressCircle> ProgressCircle;
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
