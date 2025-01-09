// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERInteractInterface.h"
#include "GameFramework/Actor.h"
#include "ERInteractableActor.generated.h"

class UWidgetComponent;

UCLASS()
class ESCAPEROOM_API AERInteractableActor : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERInteractableActor();

	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;
	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;

protected:
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

private:
	// Widget component for interact key
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact")
	TObjectPtr<UWidgetComponent> InteractKeyWidget;
};
