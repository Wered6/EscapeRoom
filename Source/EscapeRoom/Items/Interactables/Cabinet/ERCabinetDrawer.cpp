// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCabinetDrawer.h"
#include "EscapeRoom/Components/ERInteractableComponent.h"
#include "EscapeRoom/Components/ERLockComponent.h"


AERCabinetDrawer::AERCabinetDrawer()
{
	PrimaryActorTick.bCanEverTick = false;

	DrawerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DrawerMesh"));
	SetRootComponent(DrawerMesh);
	DrawerMesh->SetCollisionProfileName(TEXT("BlockAll"));

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));

	InteractableComponent = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(DrawerMesh);
}

void AERCabinetDrawer::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
#pragma region Nullchecks
	if (!InteractableComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractableComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!DrawerMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DrawerMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractableComponent->SetShowInteractWidget(bShowInteract);

	DrawerMesh->SetRenderCustomDepth(bShowInteract);
	DrawerMesh->SetCustomDepthStencilValue(bShowInteract ? 1 : 0);
}
