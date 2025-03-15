// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"
#include "GameFramework/Actor.h"
#include "ERInteractableActorBase.generated.h"

class UERInteractIconWidget;
class UBoxComponent;
class UWidgetComponent;

UCLASS()
class ESCAPEROOM_API AERInteractableActorBase : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERInteractableActorBase();

	virtual void BeginPlay() override;

	/**
	 * Sets the interaction state for this actor.
	 * @param bNewCanInteract Determines whether interaction is enabled (true) or disabled (false).
	 */
	UFUNCTION(BlueprintCallable, Category="ER|Interact")
	void SetCanInteract(const bool bNewCanInteract);
	/**
	 * Toggles the visibility of the interaction widget for this actor.
	 * @param bShow Determines whether the interaction widget should be visible (true) or hidden (false).
	 */
	void SetShowInteractWidget(const bool bShow) const;

	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;
	virtual void InteractPressStarted_Implementation(AActor* OtherInstigator) override;
	virtual void InteractPressTriggered_Implementation() override;
	virtual void InteractPressCompleted_Implementation() override;
	virtual void InteractHoldStarted_Implementation(AActor* OtherInstigator, float& OutHoldTimeThreshold) override;
	virtual void InteractHoldOngoing_Implementation(const float ElapsedSeconds) override;
	virtual void InteractHoldTriggered_Implementation() override;
	virtual void InteractHoldCanceled_Implementation() override;
	virtual void InteractHoldCompleted_Implementation() override;
	virtual bool DoesUseCustomInteractArea_Implementation() override;
	virtual bool CanInteract_Implementation() override;
	virtual EERInteractType GetInteractType_Implementation() override;

protected:
	/**
	 * Represents the actor responsible for initiating interaction with this interactable object.
	 */
	UPROPERTY(VisibleInstanceOnly, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

	/**
	 * Specifies the category of interaction (e.g., Use, Collect, Open, Unlock) for the interactable actor.
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractCategory InteractCategory{};
	/**
	 * Defines the type of interaction (e.g., Press or Hold) for the interactable actor.
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractType InteractType{};

	/**
	 * Stores a collection of mesh components used for rendering outlines or visual effects on the interactable actor.
	 */
	UPROPERTY(BlueprintReadWrite, Category="ER|Interact")
	TArray<TObjectPtr<UMeshComponent>> OutlineMeshComponents;

private:
	/**
	 * Specifies the widget class used to define the interaction UI for the interactable actor.
	 */
	UPROPERTY(EditDefaultsOnly, meta=(DisplayPriority=0), Category="ER|Interact")
	TSubclassOf<UERInteractIconWidget> InteractWidgetClass;
	/**
	 * Represents the specific interaction UI widget instance for the interactable actor.
	 */
	UPROPERTY()
	TObjectPtr<UERInteractIconWidget> InteractWidget;
	/**
     * Widget component used to display interaction UI elements for the interactable actor.
     */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InteractWidgetComp;

	/**
	 * Specifies the initial percentage value for the round progress bar in the interaction UI.
	 * Used to initialize the visual representation of interaction progress.
	 */
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="1", UIMin="0", UIMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float InitialRoundProgressbarPercent{};

	/**
	 * Defines the size of the round progress bar in the interaction widget.
	 */
	UPROPERTY(EditAnywhere, meta=(EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	FVector2D RoundProgressbarSize{100.f, 100.f};
	/**
	 * Defines the size of the icon displayed in the interaction widget.
	 */
	UPROPERTY(EditAnywhere, meta=(EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	FVector2D IconSize{50.f, 50.f};
	/**
	 * Defines the time threshold (in seconds) required for a "Hold" interaction to be triggered.
	 */
	UPROPERTY(EditAnywhere, meta=(UIMin="0", ClampMin="0", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float HoldTimeThreshold{};

	/**
	 * Indicates whether this actor can currently be interacted with.
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	bool bCanInteract{};
	/**
	 * Determines whether this actor uses a custom-defined interaction area or itself.
	 * If true add collision with collision preset "InteractArea".
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	bool bUseCustomInteractArea{};
};
