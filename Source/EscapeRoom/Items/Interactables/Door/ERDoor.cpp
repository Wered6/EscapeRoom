// Fill out your copyright notice in the Description page of Project Settings.


#include "ERDoor.h"
#include "Components/BoxComponent.h"
#include "EscapeRoom/Components/ERLockComponent.h"
#include "Kismet/GameplayStatics.h"


AERDoor::AERDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootMesh);
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));

	InteractArea->SetupAttachment(DoorMesh);

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	HandleMesh->SetupAttachment(DoorMesh);
	HandleMesh->SetCollisionProfileName(TEXT("NoCollision"));

	LockComponent = CreateDefaultSubobject<UERLockComponent>(TEXT("LockComponent"));

	OutlineMeshComponentPtr = HandleMesh;
}

void AERDoor::BeginPlay()
{
	Super::BeginPlay();

#pragma region Nullchecks
	if (!LockComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LockComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

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
