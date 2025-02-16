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

void AERFlashlight::TurnOn() const
{
	SpotLight->SetVisibility(true);
	SpotLightGlow->SetVisibility(true);
}

void AERFlashlight::TurnOff() const
{
	SpotLight->SetVisibility(false);
	SpotLightGlow->SetVisibility(false);
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

	if (OnFlashlightEquipped.IsBound())
	{
		OnFlashlightEquipped.Execute();
	}
}

void AERFlashlight::SetUltraVioletColor(const FUVGlassData& UVGlassData)
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

	SpotLight->SetLightColor(UVGlassData.BaseLight);
	SpotLightGlow->SetLightColor(UVGlassData.GlowLight);

	DynamicMaterial->SetScalarParameterValue(FName("UltraViolet"), UVGlassData.UltraVioletValue);

	// Update the postprocess settings with the dynamic material
	SceneCapture->PostProcessSettings.WeightedBlendables.Array[0] = FWeightedBlendable(1.f, DynamicMaterial);
}
