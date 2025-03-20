// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERCabinet.generated.h"

UCLASS()
class ESCAPEROOM_API AERCabinet : public AActor
{
	GENERATED_BODY()

public:
	AERCabinet();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> DoorLeft;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> DoorRight;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> DrawerFirst;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> DrawerSecond;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UChildActorComponent> DrawerThird;
};
