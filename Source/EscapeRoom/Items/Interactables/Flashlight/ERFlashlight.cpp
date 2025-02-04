// Fill out your copyright notice in the Description page of Project Settings.


#include "ERFlashlight.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"

AERFlashlight::AERFlashlight()
{
	RootMesh->SetCollisionResponseToAllChannels(ECR_Block);
	RootMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	RootMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCapture->SetupAttachment(RootMesh);
	SceneCapture->FOVAngle = 30.f;
	SceneCapture->CaptureSource = SCS_FinalColorLDR;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(SceneCapture);
	SpotLight->Intensity = 10000.f;
	SpotLight->IntensityUnits = ELightUnits::Unitless;
	SpotLight->SetVisibility(false);

	SpotLightGlow = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightGlow"));
	SpotLightGlow->SetupAttachment(SceneCapture);
	SpotLightGlow->Intensity = 10000.f;
	SpotLightGlow->IntensityUnits = ELightUnits::Unitless;
	SpotLightGlow->SetVisibility(false);

	const float FOVSceneCapture{SceneCapture->FOVAngle};
	SpotLight->SetOuterConeAngle(FOVSceneCapture / 2);
	SpotLightGlow->SetOuterConeAngle(FOVSceneCapture / 2);

	RootMesh->CastShadow = false;

	OutlineMeshComponentPtr = RootMesh;
}

void AERFlashlight::BeginPlay()
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
}

void AERFlashlight::SwitchToNextColor()
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
	// TODO Add click sound
}

void AERFlashlight::InteractStart_Implementation(AActor* OtherInstigator)
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

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Character->EquipFlashlight(this);
	RootMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// TODO try const on UltraVioletColor
void AERFlashlight::SetUltraVioletColor(EUltraVioletColor UltraVioletColor)
{
#pragma region Nullchecks
	if (!SpotLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SpotLight is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!SpotLightGlow)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SpotLightGlow is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PostProcessMask)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PostProcessMask is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Modify the material parameters at runtime
	UMaterialInstanceDynamic* DynamicMaterial{UMaterialInstanceDynamic::Create(PostProcessMask, this)};
	// TODO change all UMaterialInstanceDynamic::Create into Mesh->CreateDynamicMaterialInstance

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
		UltraVioletValue = FlashLightColorRed.UltraVioletValue;
		SpotLight->SetLightColor(FlashLightColorRed.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorRed.GlowLight);
		CurrentColor = EUltraVioletColor::EVC_Red;
		break;
	case EUltraVioletColor::EVC_Green:
		UltraVioletValue = FlashLightColorGreen.UltraVioletValue;
		SpotLight->SetLightColor(FlashLightColorGreen.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorGreen.GlowLight);
		CurrentColor = EUltraVioletColor::EVC_Green;
		break;
	case EUltraVioletColor::EVC_Blue:
		UltraVioletValue = FlashLightColorBlue.UltraVioletValue;
		SpotLight->SetLightColor(FlashLightColorBlue.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorBlue.GlowLight);
		CurrentColor = EUltraVioletColor::EVC_Blue;
		break;
	}

	DynamicMaterial->SetScalarParameterValue(FName("UltraViolet"), UltraVioletValue);

	// Update the postprocess settings with the dynamic material
	SceneCapture->PostProcessSettings.WeightedBlendables.Array[0] = FWeightedBlendable(1.f, DynamicMaterial);
}
