// Fill out your copyright notice in the Description page of Project Settings.


#include "ERFlashlight.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "EscapeRoom/InteractionSystem/ERInteractableComponent.h"
#include "EscapeRoom/Items/Interactables/UVGlass/ERUVGlass.h"

AERFlashlight::AERFlashlight()
{
	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	FlashlightMesh->SetCollisionResponseToAllChannels(ECR_Block);
	FlashlightMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	FlashlightMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	FlashlightMesh->CastShadow = false;
	SetRootComponent(FlashlightMesh);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCapture->FOVAngle = 30.f;
	SceneCapture->CaptureSource = SCS_FinalColorLDR;
	SceneCapture->SetupAttachment(FlashlightMesh);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->Intensity = 10000.f;
	SpotLight->IntensityUnits = ELightUnits::Unitless;
	SpotLight->SetVisibility(false);
	SpotLight->SetupAttachment(SceneCapture);

	SpotLightGlow = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightGlow"));
	SpotLightGlow->Intensity = 10000.f;
	SpotLightGlow->IntensityUnits = ELightUnits::Unitless;
	SpotLightGlow->SetVisibility(false);
	SpotLightGlow->SetupAttachment(SceneCapture);

	const float FOVSceneCapture{SceneCapture->FOVAngle};
	SpotLight->SetOuterConeAngle(FOVSceneCapture / 2);
	SpotLightGlow->SetOuterConeAngle(FOVSceneCapture / 2);
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

	InteractableComp->AddOutlineMeshComponent(FlashlightMesh);

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

void AERFlashlight::InteractHoldTriggered_Implementation()
{
	Super::InteractHoldTriggered_Implementation();

	AERCharacter* Character{Cast<AERCharacter>(InteractableComp->GetInteractInstigator())};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Character->EquipFlashlight(this);
	FlashlightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
