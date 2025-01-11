// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERLockItem.h"
#include "ERDoor.generated.h"

UCLASS()
class ESCAPEROOM_API AERDoor : public AERLockItem
{
	GENERATED_BODY()

public:
	AERDoor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> DoorMesh;
};
