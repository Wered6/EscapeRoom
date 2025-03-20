// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ERInteractInterface.generated.h"

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

class IERInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	void DisplayInteractionUI(const bool bShowInteract);
	/**
	 * Override this if you need an attachment point other than the root component.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	USceneComponent* GetWidgetAttachmentComponent();

	/**
	 * Called when an interaction press is initiated by an actor.
	 *
	 * @param OtherInstigator The actor initiating the interaction.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Press")
	void InteractPressStarted(AActor* OtherInstigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Press")
	void InteractPressTriggered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Press")
	void InteractPressCompleted();

	/**
	 * Called when an interaction hold is initiated by an actor.
	 *
	 * @param OtherInstigator The actor initiating the interaction.
	 * @return The hold threshold required to trigger the interaction.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(ReturnDisplayName="HoldTimeThreshold"), Category="ER|Interact|Hold")
	float InteractHoldStarted(AActor* OtherInstigator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldOngoing(const float ElapsedSeconds);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldCanceled();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldTriggered();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact|Hold")
	void InteractHoldCompleted();

	/**
	 * Meant only to be called.
	 * Do NOT override this, unless you know what are you doing.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	bool DoesUseCustomInteractArea();
	/**
	 * Meant only to be called.
	 * Do NOT override this, unless you know what are you doing.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	void SetCanInteract(const bool bNewCanInteract);
	/**
	 * Meant only to be called.
	 * Do NOT override this, unless you know what are you doing.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	bool GetCanInteract();
	/**
	 * Meant only to be called.
	 * Do NOT override this, unless you know what are you doing.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ER|Interact")
	EERInteractType GetInteractType();
};
