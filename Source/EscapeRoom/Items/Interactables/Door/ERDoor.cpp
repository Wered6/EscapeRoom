// Fill out your copyright notice in the Description page of Project Settings.


#include "ERDoor.h"
#include "EscapeRoom/Components/ERLockComponent.h"
#include "EscapeRoom/InteractionSystem/ERInteractableComponent.h"
#include "Kismet/GameplayStatics.h"


AERDoor::AERDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetCollisionProfileName(TEXT("BlockAll"));
	SetRootComponent(FrameMesh);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));
	DoorMesh->SetupAttachment(FrameMesh);

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	HandleMesh->SetCollisionProfileName(TEXT("NoCollision"));
	HandleMesh->SetupAttachment(DoorMesh);

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));
}

void AERDoor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComp->AddOutlineMeshComponent(HandleMesh);

	LockComponent->OnUnlock.BindUObject(this, &AERDoor::PlayUnlockSound);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERDoor::PlayUnlockSound()
{
#pragma region Nullchecks
	if (!UnlockSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|UnlockSound is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	UGameplayStatics::PlaySoundAtLocation(this, UnlockSound, GetActorLocation());
}
