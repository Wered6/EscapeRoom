// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERInteractInterface.h"
#include "GameFramework/Actor.h"
#include "ERInteractableActor.generated.h"

class UBoxComponent;
class UWidgetComponent;

/**
 * Class for simplest interactable objects.
 */
UCLASS()
class ESCAPEROOM_API AERInteractableActor : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERInteractableActor();

	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;
	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;

protected:
	void DisableInteraction() const;

	/**
	 * Base mesh of every interactable actor
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

	/**
	 * Pointer to player who can interact with actor
	 */
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

	/**
	 * Area to facilitate player interactions
	 * Adjust in blueprints to size of item
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Interact")
	TObjectPtr<UBoxComponent> InteractArea;

	/**
	 * Mesh which to outline, when interact, set in constructor
	 */
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> OutlineMeshComponentPtr;

private:
	/**
	 * Widget that shows when we point at interactable actor
	 */
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact")
	TObjectPtr<UWidgetComponent> InteractWidget;
};
