// Fill out your copyright notice in the Description page of Project Settings.


#include "ERUVGlass.h"
#include "EscapeRoom/Character/ERCharacter.h"


AERUVGlass::AERUVGlass()
{
	PrimaryActorTick.bCanEverTick = false;

	OutlineMeshComponentPtr = RootMesh;
}

void AERUVGlass::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	AERCharacter* Character{Cast<AERCharacter>(OtherInstigator)};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Character->CollectUVGlass(Data);

	Destroy();
}
