// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinetDrawer.h"
#include "EscapeRoom/Components/ERLockComponent.h"


AERCabinetDrawer::AERCabinetDrawer()
{
	PrimaryActorTick.bCanEverTick = false;

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));

	OutlineMeshComponentPtr = RootMesh;
}
