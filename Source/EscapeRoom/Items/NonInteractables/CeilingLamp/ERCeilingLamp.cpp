// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCeilingLamp.h"


AERCeilingLamp::AERCeilingLamp()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("NoCollision"));

	LightLeft = CreateDefaultSubobject<URectLightComponent>(TEXT("LightDownLeft"));
	LightLeft->SetupAttachment(RootMesh);
	LightLeft->SetRelativeLocation(FVector(0.f, -3.f, -30.f));
	LightLeft->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	LightLeft->SetIntensity(5000.f);
	LightLeft->SetIntensityUnits(ELightUnits::Unitless);
	LightLeft->SetSourceWidth(3.f);
	LightLeft->SetSourceHeight(120.f);
	LightLeft->SetBarnDoorAngle(90.f);
	LightLeft->SetBarnDoorLength(10.f);
	LightLeft->SetVisibility(false);

	LightRight = CreateDefaultSubobject<URectLightComponent>(TEXT("LightDownRight"));
	LightRight->SetupAttachment(RootMesh);
	LightRight->SetRelativeLocation(FVector(0.f, 3.f, -30.f));
	LightRight->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	LightRight->SetIntensity(5000.f);
	LightRight->SetIntensityUnits(ELightUnits::Unitless);
	LightRight->SetSourceWidth(3.f);
	LightRight->SetSourceHeight(120.f);
	LightRight->SetBarnDoorAngle(90.f);
	LightRight->SetBarnDoorLength(10.f);
	LightRight->SetVisibility(false);

	HelpLight = CreateDefaultSubobject<URectLightComponent>(TEXT("LightUp"));
	HelpLight->SetupAttachment(RootMesh);
	HelpLight->SetRelativeLocation(FVector(0.f, 0.f, -81.f));
	HelpLight->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	HelpLight->SetIntensity(1000.f);
	HelpLight->SetIntensityUnits(ELightUnits::Unitless);
	HelpLight->SetSourceWidth(10.f);
	HelpLight->SetSourceHeight(120.f);
	HelpLight->SetBarnDoorAngle(90.f);
	HelpLight->SetBarnDoorLength(15.f);
	HelpLight->SetCastShadows(false);
	HelpLight->SetVisibility(false);
}

void AERCeilingLamp::TurnLights() const
{
	LightLeft->ToggleVisibility();
	LightRight->ToggleVisibility();
	HelpLight->ToggleVisibility();
}
