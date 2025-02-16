// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCeilingLamp.h"


AERCeilingLamp::AERCeilingLamp()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("NoCollision"));

	LightRight = CreateDefaultSubobject<URectLightComponent>(TEXT("LightRight"));
	LightRight->SetupAttachment(RootMesh);
	LightRight->SetRelativeLocation(FVector(0.f, -3.f, -30.f));
	LightRight->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	LightRight->SetIntensity(500.f);
	LightRight->SetIntensityUnits(ELightUnits::Unitless);
	LightRight->SetSourceWidth(3.f);
	LightRight->SetSourceHeight(120.f);
	LightRight->SetBarnDoorAngle(90.f);
	LightRight->SetBarnDoorLength(10.f);
	LightRight->SetVisibility(false);

	LightLeft = CreateDefaultSubobject<URectLightComponent>(TEXT("LightLeft"));
	LightLeft->SetupAttachment(RootMesh);
	LightLeft->SetRelativeLocation(FVector(0.f, 3.f, -30.f));
	LightLeft->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	LightLeft->SetIntensity(500.f);
	LightLeft->SetIntensityUnits(ELightUnits::Unitless);
	LightLeft->SetSourceWidth(3.f);
	LightLeft->SetSourceHeight(120.f);
	LightLeft->SetBarnDoorAngle(90.f);
	LightLeft->SetBarnDoorLength(10.f);
	LightLeft->SetVisibility(false);

	HelpLight = CreateDefaultSubobject<URectLightComponent>(TEXT("HelpLight"));
	HelpLight->SetupAttachment(RootMesh);
	HelpLight->SetRelativeLocation(FVector(0.f, 0.f, -120.f));
	HelpLight->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	HelpLight->SetIntensity(200.f);
	HelpLight->SetIntensityUnits(ELightUnits::Unitless);
	HelpLight->SetSourceWidth(10.f);
	HelpLight->SetSourceHeight(120.f);
	HelpLight->SetBarnDoorAngle(90.f);
	HelpLight->SetBarnDoorLength(15.f);
	HelpLight->SetCastShadows(true);
	HelpLight->SetVisibility(false);
}

void AERCeilingLamp::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	LightDynMat = RootMesh->CreateDynamicMaterialInstance(0);
	LightRight->SetVisibility(bLightOn);
	LightLeft->SetVisibility(bLightOn);
	HelpLight->SetVisibility(bLightOn);
	UpdateLightsEmissive();
}

void AERCeilingLamp::TurnLights() const
{
	LightRight->ToggleVisibility();
	LightLeft->ToggleVisibility();
	HelpLight->ToggleVisibility();
	UpdateLightsEmissive();
}

void AERCeilingLamp::UpdateLightsEmissive() const
{
	LightDynMat->SetScalarParameterValue(FName("EmissiveLeft"), LightRight->IsVisible() ? EmissiveStrength : 0.f);
	LightDynMat->SetScalarParameterValue(FName("EmissiveRight"), LightLeft->IsVisible() ? EmissiveStrength : 0.f);
}
