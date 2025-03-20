// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractablePawnBase.h"
#include "ERInteractableComponent.h"


AERInteractablePawnBase::AERInteractablePawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableComp = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComp"));
}

void AERInteractablePawnBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
	InteractableComp->DisplayInteractionUI(bShowInteract);
}

void AERInteractablePawnBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractableComp->InteractPressStarted(OtherInstigator);
}

void AERInteractablePawnBase::InteractPressTriggered_Implementation()
{
	InteractableComp->InteractPressTriggered();
}

void AERInteractablePawnBase::InteractPressCompleted_Implementation()
{
	InteractableComp->InteractPressCompleted();
}

float AERInteractablePawnBase::InteractHoldStarted_Implementation(AActor* OtherInstigator)
{
	return InteractableComp->InteractHoldStarted(OtherInstigator);
}

void AERInteractablePawnBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
	InteractableComp->InteractHoldOngoing(ElapsedSeconds);
}

void AERInteractablePawnBase::InteractHoldTriggered_Implementation()
{
	InteractableComp->InteractHoldTriggered();
}

void AERInteractablePawnBase::InteractHoldCanceled_Implementation()
{
	InteractableComp->InteractHoldCanceled();
}

void AERInteractablePawnBase::InteractHoldCompleted_Implementation()
{
	InteractableComp->InteractHoldCompleted();
}

bool AERInteractablePawnBase::DoesUseCustomInteractArea_Implementation()
{
	return InteractableComp->DoesUseCustomInteractArea();
}

void AERInteractablePawnBase::SetCanInteract_Implementation(const bool bNewCanInteract)
{
	InteractableComp->SetCanInteract(bNewCanInteract);
}

bool AERInteractablePawnBase::GetCanInteract_Implementation()
{
	return InteractableComp->GetCanInteract();
}

EERInteractType AERInteractablePawnBase::GetInteractType_Implementation()
{
	return InteractableComp->GetInteractType();
}
