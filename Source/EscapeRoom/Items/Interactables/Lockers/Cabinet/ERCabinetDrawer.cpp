// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinetDrawer.h"


AERCabinetDrawer::AERCabinetDrawer()
{
	PrimaryActorTick.bCanEverTick = false;

	OutlineMeshComponentPtr = RootMesh;
}
