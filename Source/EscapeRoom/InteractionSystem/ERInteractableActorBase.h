// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERInteractInterface.h"
#include "GameFramework/Actor.h"
#include "ERInteractableActorBase.generated.h"

class UERInteractableComponent;

UCLASS()
class ESCAPEROOM_API AERInteractableActorBase : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERInteractableActorBase();

	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;

	virtual void InteractPressStarted_Implementation(AActor* OtherInstigator) override;
	virtual void InteractPressTriggered_Implementation() override;
	virtual void InteractPressCompleted_Implementation() override;

	virtual float InteractHoldStarted_Implementation(AActor* OtherInstigator) override;
	virtual void InteractHoldOngoing_Implementation(const float ElapsedSeconds) override;
	virtual void InteractHoldTriggered_Implementation() override;
	virtual void InteractHoldCanceled_Implementation() override;
	virtual void InteractHoldCompleted_Implementation() override;

	virtual bool DoesUseCustomInteractArea_Implementation() override;
	virtual void SetCanInteract_Implementation(const bool bNewCanInteract) override;
	virtual bool GetCanInteract_Implementation() override;
	virtual EERInteractType GetInteractType_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UERInteractableComponent> InteractableComp;
};
