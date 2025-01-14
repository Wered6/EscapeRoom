// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERCabinet.generated.h"

class AERCabinetDrawer;
class AERCabinetDoor;

UCLASS()
class ESCAPEROOM_API AERCabinet : public AActor
{
	GENERATED_BODY()

public:
	AERCabinet();

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(EditAnywhere, Category="ER|Drawers")
	TObjectPtr<UChildActorComponent> DoorLeft;
	UPROPERTY(EditAnywhere, Category="ER|Drawers")
	TObjectPtr<UChildActorComponent> DoorRight;

	UPROPERTY(EditAnywhere, Category="ER|Drawers")
	TObjectPtr<UChildActorComponent> DrawerFirst;
	UPROPERTY(EditAnywhere, Category="ER|Drawers")
	TObjectPtr<UChildActorComponent> DrawerSecond;
	UPROPERTY(EditAnywhere, Category="ER|Drawers")
	TObjectPtr<UChildActorComponent> DrawerThird;
};
