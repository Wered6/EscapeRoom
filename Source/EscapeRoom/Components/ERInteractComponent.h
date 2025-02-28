// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERInteractComponent.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * Enable character to interact with Actor which has InteractInterface
 */
UCLASS(ClassGroup=(Interact), meta=(BlueprintSpawnableComponent))
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
	 * Stops performing interaction check but InteractableActor stays set
	 */
	FORCEINLINE void SetCanCheckInteraction(const bool bValue)
	{
		bCanCheckInteraction = bValue;
	}

private:
	void PerformInteractionCheck();
	void ClearInteraction();

	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractableActor;
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> InteractableHitComponent;

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	float InteractionDistance{200.f};
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	bool bCanCheckInteraction{true};

	/** Character interact component belongs to */
	UPROPERTY()
	TObjectPtr<ACharacter> CharacterOwner;

#pragma region Input

private:
	/**
	* Call for interact action
	*/
	void Interact();

	UPROPERTY(EditDefaultsOnly, Category="ER|Interact|Input")
	TObjectPtr<UInputMappingContext> InteractMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact|Input")
	TObjectPtr<UInputAction> InteractAction;

#pragma endregion
};
