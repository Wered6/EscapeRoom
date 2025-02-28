// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERInteractInterface.h"
#include "GameFramework/Pawn.h"
#include "ERInteractablePawnBase.generated.h"

class UWidgetComponent;
class UBoxComponent;

/**
 * Class for interactable objects that can be possessed.
 */
UCLASS()
class ESCAPEROOM_API AERInteractablePawnBase : public APawn, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERInteractablePawnBase();

	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;
	virtual void DisplayInteractionUI_Implementation(const bool bShowInteract) override;

protected:
	void EnableInteraction() const;
	void DisableInteraction() const;

	/**
	 * Base mesh of every interactable object
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

	/**
	 * Pointer to player who can interact with Pawn
	 */
	UPROPERTY(VisibleAnywhere, Category="ER|Interact")
	TObjectPtr<AActor> InteractInstigator;

	/**
	 * Area to facilitate player interactions
	 * Adjust size in blueprints
	 */
	UPROPERTY(EditAnywhere, Category="ER|Interact")
	TObjectPtr<UBoxComponent> InteractArea;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> OutlineMeshComponentPtr;

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Interact")
	TObjectPtr<UWidgetComponent> InteractWidget;
};
