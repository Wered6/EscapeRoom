// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "ERInteractableComponent.generated.h"

class UERInteractIconWidget;
class UWidgetComponent;
enum class EERInteractType : uint8;
enum class EERInteractCategory : uint8;

/**
 * Component that has all info about interactable object, works only if object has implemented interact interface
 */
UCLASS(ClassGroup=(Interact))
class ESCAPEROOM_API UERInteractableComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UERInteractableComponent();

	virtual void OnRegister() override;

	virtual void BeginPlay() override;

	void SetCanInteract(bool bCanInteract);

	AActor* GetInteractInstigator()
	{
		return InteractInstigator;
	}

	FORCEINLINE void SetInteractInstigator(AActor* Actor)
	{
		InteractInstigator = Actor;
	}

	void SetShowInteractWidget(const bool bShow) const;

private:
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractCategory InteractCategory{};
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractType InteractType{};

	/**
	* Widget that appears when we point at interactable object
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InteractWidgetComp;
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact")
	TSubclassOf<UERInteractIconWidget> InteractWidgetClass;
	UPROPERTY()
	TObjectPtr<UERInteractIconWidget> InteractWidget;
};
