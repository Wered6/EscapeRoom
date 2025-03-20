// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableActorBase.h"
#include "ERInteractableComponent.h"


AERInteractableActorBase::AERInteractableActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableComp = CreateDefaultSubobject<UERInteractableComponent>(TEXT("InteractableComp"));
}

void AERInteractableActorBase::DisplayInteractionUI_Implementation(const bool bShowInteract)
{
	InteractableComp->DisplayInteractionUI(bShowInteract);
}

void AERInteractableActorBase::InteractPressStarted_Implementation(AActor* OtherInstigator)
{
	InteractableComp->InteractPressStarted(OtherInstigator);
}

void AERInteractableActorBase::InteractPressTriggered_Implementation()
{
	InteractableComp->InteractPressTriggered();
}

void AERInteractableActorBase::InteractPressCompleted_Implementation()
{
	InteractableComp->InteractPressCompleted();
}

float AERInteractableActorBase::InteractHoldStarted_Implementation(AActor* OtherInstigator)
{
	return InteractableComp->InteractHoldStarted(OtherInstigator);
}

void AERInteractableActorBase::InteractHoldOngoing_Implementation(const float ElapsedSeconds)
{
	InteractableComp->InteractHoldOngoing(ElapsedSeconds);
}

void AERInteractableActorBase::InteractHoldTriggered_Implementation()
{
	InteractableComp->InteractHoldTriggered();
}

void AERInteractableActorBase::InteractHoldCanceled_Implementation()
{
	InteractableComp->InteractHoldCanceled();
}

void AERInteractableActorBase::InteractHoldCompleted_Implementation()
{
	InteractableComp->InteractHoldCompleted();
}

bool AERInteractableActorBase::DoesUseCustomInteractArea_Implementation()
{
	return InteractableComp->DoesUseCustomInteractArea();
}

void AERInteractableActorBase::SetCanInteract_Implementation(const bool bNewCanInteract)
{
	InteractableComp->SetCanInteract(bNewCanInteract);
}

bool AERInteractableActorBase::GetCanInteract_Implementation()
{
	return InteractableComp->GetCanInteract();
}

EERInteractType AERInteractableActorBase::GetInteractType_Implementation()
{
	return InteractableComp->GetInteractType();
}
