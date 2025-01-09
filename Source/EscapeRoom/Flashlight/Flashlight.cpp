// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"

AFlashlight::AFlashlight()
{
	PrimaryActorTick.bCanEverTick = false;

	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	SetRootComponent(FlashlightMesh);
	FlashlightMesh->SetCollisionResponseToAllChannels(ECR_Block);
	FlashlightMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	FlashlightMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FlashlightMesh->SetCastShadow(false);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCapture->SetupAttachment(FlashlightMesh);
	SceneCapture->FOVAngle = 30.f;
	SceneCapture->CaptureSource = SCS_FinalColorLDR;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(SceneCapture);
	SpotLight->Intensity = 100000.f;
	SpotLight->IntensityUnits = ELightUnits::Unitless;
	SpotLight->SetVisibility(false);

	SpotLightGlow = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightGlow"));
	SpotLightGlow->SetupAttachment(SceneCapture);
	SpotLightGlow->Intensity = 100000.f;
	SpotLightGlow->IntensityUnits = ELightUnits::Unitless;
	SpotLightGlow->SetVisibility(false);

	const float FOVSceneCapture{SceneCapture->FOVAngle};
	SpotLight->SetOuterConeAngle(FOVSceneCapture / 2);
	SpotLightGlow->SetOuterConeAngle(FOVSceneCapture / 2);
}

void AFlashlight::BeginPlay()
{
	// code is before Super::BeginPlay because it has to be called before blueprint's BeginPlay
#pragma region Nullchecks
	if (!PostProcessMask)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PP_Mask is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!SceneCapture)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SceneCapture is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Apply the PostProcessMaterial dynamically
	SceneCapture->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1.f, PostProcessMask));

	Super::BeginPlay();

	// TODO try to set decals to full invisible
	// TODO using metal isn't good, find something else
	// TODO try combine translucent hole mask in M_Sign
}

void AFlashlight::SwitchToNextColor()
{
	switch (CurrentColor)
	{
	case EUltraVioletColor::EVC_Off:
		SetUltraVioletColor(EUltraVioletColor::EVC_White);
		break;
	case EUltraVioletColor::EVC_White:
		SetUltraVioletColor(EUltraVioletColor::EVC_Red);
		break;
	case EUltraVioletColor::EVC_Red:
		SetUltraVioletColor(EUltraVioletColor::EVC_Green);
		break;
	case EUltraVioletColor::EVC_Green:
		SetUltraVioletColor(EUltraVioletColor::EVC_Blue);
		break;
	case EUltraVioletColor::EVC_Blue:
		SetUltraVioletColor(EUltraVioletColor::EVC_Off);
		break;
	}
}

void AFlashlight::InteractStart_Implementation(AActor* OtherInstigator)
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

	Character->EquipFlashlight(this);
	FlashlightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// TODO try const on UltraVioletColor
void AFlashlight::SetUltraVioletColor(EUltraVioletColor UltraVioletColor)
{
	// Modify the material parameters at runtime
	UMaterialInstanceDynamic* DynamicMaterial{UMaterialInstanceDynamic::Create(PostProcessMask, this)};

#pragma region Nullchecks
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	float UltraVioletValue{0.f};
	switch (UltraVioletColor)
	{
	case EUltraVioletColor::EVC_Off:
		SpotLight->SetVisibility(false);
		SpotLightGlow->SetVisibility(false);
		CurrentColor = EUltraVioletColor::EVC_Off;
		break;
	case EUltraVioletColor::EVC_White:
		SpotLight->SetVisibility(true);
		SpotLightGlow->SetVisibility(true);
		UltraVioletValue = 0.f;
		SpotLight->SetLightColor(FLinearColor(FColor::White));
		SpotLightGlow->SetLightColor(FLinearColor(FColor::White));
		CurrentColor = EUltraVioletColor::EVC_White;
		break;
	case EUltraVioletColor::EVC_Red:
		UltraVioletValue = 0.03f;
		SpotLight->SetLightColor(FlashLightColorRed.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorRed.GlowLight);
		CurrentColor = EUltraVioletColor::EVC_Red;
		break;
	case EUltraVioletColor::EVC_Green:
		UltraVioletValue = 0.05f;
		SpotLight->SetLightColor(FlashLightColorGreen.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorGreen.GlowLight);
		CurrentColor = EUltraVioletColor::EVC_Green;
		break;
	case EUltraVioletColor::EVC_Blue:
		UltraVioletValue = 0.04f;
		SpotLight->SetLightColor(FlashLightColorBlue.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorBlue.GlowLight);
		CurrentColor = EUltraVioletColor::EVC_Blue;
		break;
	}

	DynamicMaterial->SetScalarParameterValue(FName("UltraViolet"), UltraVioletValue);

	// Update the postprocess settings with the dynamic material
	SceneCapture->PostProcessSettings.WeightedBlendables.Array[0] = FWeightedBlendable(1.f, DynamicMaterial);
}
