// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERInteractableComponent.generated.h"

class UWidgetComponent;
class UERInteractIconWidget;
enum class EERInteractType : uint8;
enum class EERInteractCategory : uint8;

/**
 * This component provides support for implementing interactable objects and handling player interaction logic.
 * Only for InteractableActorBase, InteractablePawnBase, InteractableCharacterBase.
 */
UCLASS(NotBlueprintable, NotBlueprintType)
class ESCAPEROOM_API UERInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UERInteractableComponent();

	virtual void BeginPlay() override;

	void SetInteractInstigator(AActor* Instigator)
	{
		InteractInstigator = Instigator;
	}

	AActor* GetInteractInstigator() const
	{
		return InteractInstigator;
	}

	UFUNCTION(BlueprintCallable, Category="ER|Interact")
	void AddOutlineMeshComponent(UMeshComponent* MeshComponent);
	UFUNCTION(BlueprintCallable, Category="ER|Interact")
	void SetOutlineMeshComponents(const TArray<UMeshComponent*>& NewOutlineMeshComponents);

	// Interact interface functions begin

	void DisplayInteractionUI(const bool bShowInteract);

	void InteractPressStarted(AActor* OtherInstigator);
	void InteractPressTriggered();
	void InteractPressCompleted();

	float InteractHoldStarted(AActor* OtherInstigator);
	void InteractHoldOngoing(const float ElapsedSeconds);
	void InteractHoldTriggered();
	void InteractHoldCanceled();
	void InteractHoldCompleted();

	bool DoesUseCustomInteractArea() const;
	void SetCanInteract(const bool bNewCanInteract);
	bool GetCanInteract() const;
	EERInteractType GetInteractType() const;

	// Interact interface functions end

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractCategory InteractCategory{};
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractType InteractType{};

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	FVector2D IconSize{50.f, 50.f};

	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalIconOpacity{0.3f};
	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalProgressCircleOpacity{};
	UPROPERTY(EditAnywhere, meta=(EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	FVector2D ProgressCircleSize{100.f, 100.f};

	/**
	 * Required time duration (in seconds) to trigger and complete a hold interaction (it's one shot hold trigger).
	 */
	UPROPERTY(EditAnywhere, meta=(UIMin="0", ClampMin="0", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float HoldTimeThreshold{};

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	bool bCanInteract{};
	/**
	 * Determines whether a custom interaction area is used for this interactable object.
	 * If true, add collision with preset "InteractArea".
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	bool bUseCustomInteractArea{};

protected:
	virtual void OnRegister() override;

private:
	void InitializeInteractWidget();
	void UpdateWidgetAttachment() const;

	/**
	 * Pointer to the actor initiating the interaction, updated during interaction events.
	 * Used to track and manage the instigator of a specific interaction session.
	 */
	UPROPERTY(VisibleInstanceOnly, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	TArray<TObjectPtr<UMeshComponent>> OutlineMeshComps;

	/**
	 * Defines the widget class used to represent the interaction UI.
	 * By default widget comp is attached to root.
	 * You can override GetWidgetAttachment function from interact interface to specify new attachment.
	 */
	UPROPERTY(EditDefaultsOnly, meta=(DisplayPriority=0), Category="ER|Interact")
	TSubclassOf<UERInteractIconWidget> InteractWidgetClass;

	UPROPERTY()
	TObjectPtr<UERInteractIconWidget> InteractWidget;
	UPROPERTY()
	TObjectPtr<UWidgetComponent> InteractWidgetComp;
};
