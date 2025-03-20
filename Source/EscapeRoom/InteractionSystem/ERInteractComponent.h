// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERInteractComponent.generated.h"

struct FInputActionInstance;
class UInputAction;
class UInputMappingContext;

/**
 * Component that enables character to interact with object which has InteractInterface
 */
UCLASS(ClassGroup=(Interact))
class ESCAPEROOM_API UERInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UERInteractComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/**
	 * Stops performing interaction check but InteractableActor stay set
	 */
	FORCEINLINE void SetCanCheckInteraction(const bool bValue)
	{
		bCanCheckInteraction = bValue;
	}

private:
	void PerformInteractionCheck();
	void SetInteraction(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	void ClearInteraction();

	/**
	 * Reference to the actor currently being interacted with.
	 */
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractableActor;
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> InteractableHitComponent;

	/**
	 * The maximum distance at which interaction with an object can occur.
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	float InteractionDistance{200.f};
	/**
	 * Determines if interaction checks can be performed.
	 */
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	bool bCanCheckInteraction{true};

	UPROPERTY()
	TObjectPtr<ACharacter> CharacterOwner;

#pragma region Input

private:
	void InteractPressStarted();
	void InteractPressTriggered();
	void InteractPressCompleted();

	void InteractHoldStarted(const FInputActionInstance& Instance);
	void InteractHoldOngoing(const FInputActionInstance& Instance);
	void InteractHoldCanceled();
	void InteractHoldTriggered();
	void InteractHoldCompleted();

	UPROPERTY(EditDefaultsOnly, Category="ER|Interact|Input")
	TObjectPtr<UInputMappingContext> InteractMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact|Input")
	TObjectPtr<UInputAction> InteractPressAction;
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact|Input")
	TObjectPtr<UInputAction> InteractHoldAction;

#pragma endregion
};
