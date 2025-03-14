// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EscapeRoom/Items/Interactables/ERInteractInterface.h"
#include "ERPicture.generated.h"

class UERInteractableComponent;

UCLASS()
class ESCAPEROOM_API AERPicture : public AActor, public IERInteractInterface
{
	GENERATED_BODY()

public:
	AERPicture();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERInteractableComponent> InteractableComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FrameMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> PaintingMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> BackMesh;
};
