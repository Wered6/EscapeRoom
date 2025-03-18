// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERInteractableComponent.generated.h"

class UWidgetComponent;
class UERInteractIconWidget;
enum class EERInteractType : uint8;
enum class EERInteractCategory : uint8;
class AERInteractableCharacterBase;
class AERInteractablePawnBase;
class AERInteractableActorBase;

/**
 * This component provides support for implementing interactable objects and handling player interaction logic.
 * Only for InteractableActorBase, InteractablePawnBase, InteractableCharacterBase.
 */
UCLASS()
class ESCAPEROOM_API UERInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

	friend AERInteractableActorBase;
	friend AERInteractablePawnBase;
	friend AERInteractableCharacterBase;

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
	void InteractHoldStarted(AActor* OtherInstigator, float& OutHoldTimeThreshold);
	void InteractHoldOngoing(const float ElapsedSeconds);
	void InteractHoldTriggered();
	void InteractHoldCanceled();
	void InteractHoldCompleted();
	bool DoesUseCustomInteractArea() const;
	void SetCanInteract(const bool bNewCanInteract);
	bool GetCanInteract() const;
	EERInteractType GetInteractType() const;

	// Interact interface functions end

private:
	UPROPERTY(VisibleInstanceOnly, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractCategory InteractCategory{};
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	EERInteractType InteractType{};

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category="ER|Interact")
	TArray<TObjectPtr<UMeshComponent>> OutlineMeshComps;

	UPROPERTY(EditDefaultsOnly, meta=(DisplayPriority=0), Category="ER|Interact")
	TSubclassOf<UERInteractIconWidget> InteractWidgetClass;
	UPROPERTY()
	TObjectPtr<UERInteractIconWidget> InteractWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> InteractWidgetComp;

	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1"), Category="ER|Interact")
	float InitialIconOpacity{};
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	FVector2D IconSize{50.f, 50.f};

	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalIconOpacity{};
	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float MinimalProgressCircleOpacity{};
	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float InitialProgressCircleOpacity{};
	UPROPERTY(EditAnywhere, meta=(EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	FVector2D ProgressCircleSize{100.f, 100.f};
	UPROPERTY(EditAnywhere, meta=(UIMin="0", UIMax="1", ClampMin="0", ClampMax="1", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float InitialProgressCirclePercent{};

	UPROPERTY(EditAnywhere, meta=(UIMin="0", ClampMin="0", EditCondition="InteractType==EERInteractType::Hold"), Category="ER|Interact")
	float HoldTimeThreshold{};

	UPROPERTY(EditAnywhere, Category="ER|Interact")
	bool bCanInteract{};
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	bool bUseCustomInteractArea{};
};
