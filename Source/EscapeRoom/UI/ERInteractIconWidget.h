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
	          const float NewRoundProgressbarPercent,
	          const FVector2D NewRoundProgressbarSize,
	          const FVector2D NewIconSize);

	void SetProgressbarPercent(const float Percent) const;
	void SetSize(const FVector2D NewRoundProgressbarSize, const FVector2D NewIconSize) const;

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
	float InitialRoundProgressbarPercent{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	FVector2D RoundProgressbarSize{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	FVector2D IconSize{};

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	bool bIsHolding{};

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess=true), Category="ER|Interact")
	TObjectPtr<UERRoundProgressbar> RoundProgressbar;
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
