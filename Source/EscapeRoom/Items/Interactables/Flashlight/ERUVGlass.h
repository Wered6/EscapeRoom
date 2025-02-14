// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERUVGlass.generated.h"

USTRUCT(BlueprintType)
struct FUVGlassData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FLinearColor BaseLight{};
	UPROPERTY(EditDefaultsOnly)
	FLinearColor GlowLight{};
	UPROPERTY(EditDefaultsOnly)
	float UltraVioletValue{};
};

UCLASS()
class ESCAPEROOM_API AERUVGlass : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERUVGlass();

	/**
	 * Overriding InteractStart function from ERInteractableInterface (derived from ERInteractableActor)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|UVGlass")
	FUVGlassData Data;
	// TODO material MI_Glass doenst show outline
};
