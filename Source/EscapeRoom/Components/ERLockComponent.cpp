// Fill out your copyright notice in the Description page of Project Settings.


#include "ERLockComponent.h"


UERLockComponent::UERLockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UERLockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UERLockComponent::Unlock()
{
	if (OnUnlock.IsBound())
	{
		OnUnlock.Execute();
	}

	bLocked = false;
}

void UERLockComponent::Lock()
{
	bLocked = true;
}
