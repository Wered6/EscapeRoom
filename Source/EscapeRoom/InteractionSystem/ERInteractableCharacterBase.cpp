// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableCharacterBase.h"
#include "ERInteractableComponent.h"


AERInteractableCharacterBase::AERInteractableCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableComp = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComp"));
}

void AERInteractableCharacterBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
	InteractableComp->DisplayInteractionUI(bShowInteract);
}

void AERInteractableCharacterBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractableComp->InteractPressStarted(OtherInstigator);
}

void AERInteractableCharacterBase::InteractPressTriggered_Implementation()
{
	InteractableComp->InteractPressTriggered();
}

void AERInteractableCharacterBase::InteractPressCompleted_Implementation()
{
	InteractableComp->InteractPressCompleted();
}

float AERInteractableCharacterBase::InteractHoldStarted_Implementation(AActor* OtherInstigator)
{
	return InteractableComp->InteractHoldStarted(OtherInstigator);
}

void AERInteractableCharacterBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
	InteractableComp->InteractHoldOngoing(ElapsedSeconds);
}

void AERInteractableCharacterBase::InteractHoldTriggered_Implementation()
{
	InteractableComp->InteractHoldTriggered();
}

void AERInteractableCharacterBase::InteractHoldCanceled_Implementation()
{
	InteractableComp->InteractHoldCanceled();
}

void AERInteractableCharacterBase::InteractHoldCompleted_Implementation()
{
	InteractableComp->InteractHoldCompleted();
}

bool AERInteractableCharacterBase::DoesUseCustomInteractArea_Implementation()
{
	return InteractableComp->DoesUseCustomInteractArea();
}

void AERInteractableCharacterBase::SetCanInteract_Implementation(const bool bNewCanInteract)
{
	InteractableComp->SetCanInteract(bNewCanInteract);
}

bool AERInteractableCharacterBase::GetCanInteract_Implementation()
{
	return InteractableComp->GetCanInteract();
}

EERInteractType AERInteractableCharacterBase::GetInteractType_Implementation()
{
	return InteractableComp->GetInteractType();
}
