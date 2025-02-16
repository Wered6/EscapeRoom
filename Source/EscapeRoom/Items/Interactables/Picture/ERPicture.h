// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractableActor.h"
#include "ERPicture.generated.h"

UCLASS()
class ESCAPEROOM_API AERPicture : public AERInteractableActor
{
	GENERATED_BODY()

public:
	AERPicture();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> PaintingMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> BackMesh;
};
