// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"

AFlashlight::AFlashlight()
{
	PrimaryActorTick.bCanEverTick = false;

	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	SetRootComponent(FlashlightMesh);

	FlashlightMesh->SetCollisionResponseToAllChannels(ECR_Block);
	FlashlightMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	FlashlightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickUpSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	PickUpSphere->SetupAttachment(RootComponent);
	PickUpSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickUpSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickUpSphere->InitSphereRadius(100.f);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	SceneCapture->SetupAttachment(PickUpSphere);
	SceneCapture->FOVAngle = 30.f;
	SceneCapture->CaptureSource = SCS_FinalColorLDR;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(SceneCapture);
	SpotLight->Intensity = 100000.f;
	SpotLight->IntensityUnits = ELightUnits::Unitless;

	SpotLightGlow = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightGlow"));
	SpotLightGlow->SetupAttachment(SceneCapture);
	SpotLightGlow->Intensity = 100000.f;
	SpotLightGlow->IntensityUnits = ELightUnits::Unitless;

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
#pragma endregion

	// Apply the PostProcessMaterial dynamically
	SceneCapture->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1.f, PostProcessMask));

	SetUltraVioletColor(EUltraVioletColor::EVC_Blue);

	Super::BeginPlay();

	PickupWidget->SetVisibility(false);

	// TODO try to set decals to full invisible
	// todo why red is working
	// TODO we don't generate overlap events
}

void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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
	case EUltraVioletColor::EVC_Red:
		UltraVioletValue = 0.03f;
		SpotLight->SetLightColor(FlashLightColorRed.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorRed.GlowLight);
		break;
	case EUltraVioletColor::EVC_Blue:
		UltraVioletValue = 0.04f;
		SpotLight->SetLightColor(FlashLightColorBlue.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorBlue.GlowLight);
		break;
	case EUltraVioletColor::EVC_Green:
		UltraVioletValue = 0.05f;
		SpotLight->SetLightColor(FlashLightColorGreen.BaseLight);
		SpotLightGlow->SetLightColor(FlashLightColorGreen.GlowLight);
		break;
	}

	DynamicMaterial->SetScalarParameterValue(FName("UltraViolet"), UltraVioletValue);

	// Update the postprocess settings with the dynamic material
	SceneCapture->PostProcessSettings.WeightedBlendables.Array[0] = FWeightedBlendable(1.f, DynamicMaterial);
}

void AFlashlight::ShowPickupWidget(const bool bShowWidget) const
{
#pragma region Nullchecks
	if (!PickupWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PickupWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	PickupWidget->SetVisibility(bShowWidget);
}

void AFlashlight::SetIsEquipped()
{
	bIsEquipped = true;

	ShowPickupWidget(false);
}

void AFlashlight::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
                                  AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex,
                                  bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	AERCharacter* Character{Cast<AERCharacter>(OtherActor)};
	if (Character)
	{
		Character->SetOverlappingFlashlight(this);
	}
}

void AFlashlight::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                     AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp,
                                     int32 OtherBodyIndex)
{
	AERCharacter* Character{Cast<AERCharacter>(OtherActor)};
	if (Character)
	{
		Character->SetOverlappingFlashlight(nullptr);
	}
}
