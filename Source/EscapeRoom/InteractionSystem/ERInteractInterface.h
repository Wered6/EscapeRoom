// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERInteractInterface.generated.h"

class UWidgetComponent;

UENUM(BlueprintType)
enum class EERInteractType : uint8
{
	Press,
	Hold
};

UENUM(BlueprintType)
enum class EERInteractCategory : uint8
{
	Use,
	Collect,
	Open,
	Unlock
};

UINTERFACE()
class UERInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Remember: Use call to parent in blueprint if u want functionality from C++ and blueprints
 */
class IERInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	void DisplayInteractionUI(const bool bShowInteract);

	/** Interact press functions */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Press")
	void InteractPressStarted(AActor* OtherInstigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Press")
	void InteractPressTriggered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Press")
	void InteractPressCompleted();

	/** Interact hold functions */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldStarted(AActor* OtherInstigator, float& HoldTimeThreshold);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldOngoing(const float ElapsedSeconds);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldCanceled();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldTriggered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldCompleted();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	bool DoesUseCustomInteractArea();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	void SetCanInteract(const bool bCanInteract);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	bool GetCanInteract();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	USceneComponent* GetWidgetAttachmentComponent();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	EERInteractType GetInteractType();
};
