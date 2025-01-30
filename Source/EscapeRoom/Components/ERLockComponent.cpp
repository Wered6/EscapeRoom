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
	bLocked = false;
}

void UERLockComponent::Lock()
{
	bLocked = true;
}
