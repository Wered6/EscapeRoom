// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/InteractionSystem/ERInteractableActorBase.h"
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
class ESCAPEROOM_API AERUVGlass : public AERInteractableActorBase
{
	GENERATED_BODY()

public:
	AERUVGlass();

	virtual void InteractHoldTriggered_Implementation() override;
	virtual void InteractHoldCompleted_Implementation() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|UVGlass")
	FUVGlassData Data;
	// TODO material MI_Glass doesnt show outline

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> GlassMesh;
};
