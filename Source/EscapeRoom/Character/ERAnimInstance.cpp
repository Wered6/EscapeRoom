// Fill out your copyright notice in the Description page of Project Settings.


#include "ERAnimInstance.h"
#include "ERCharacter.h"

void UERAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ERCharacter = Cast<AERCharacter>(TryGetPawnOwner());
}

void UERAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!ERCharacter)
	{
		ERCharacter = Cast<AERCharacter>(TryGetPawnOwner());
	}
	if (!ERCharacter)
	{
		return;
	}

	bHasFlashlight = ERCharacter->HasFlashlight();
	EquippedFlashlight = ERCharacter->GetEquippedFlashlight();
}
