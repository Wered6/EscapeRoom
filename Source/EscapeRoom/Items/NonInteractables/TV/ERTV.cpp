// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTV.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Runtime/MediaAssets/Public/MediaSoundComponent.h"


AERTV::AERTV()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("NoCollision"));

	TVScreenWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TVWidget"));
	TVScreenWidget->SetupAttachment(RootMesh);
	// Hide widget from screen in scene
	TVScreenWidget->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	TVScreenWidget->SetDrawSize(FVector2D(1080.f, 1080.f));

	FilmSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("FilmSound"));
	FilmSound->SetupAttachment(RootMesh);
	FilmSound->bAllowSpatialization = true;
	FilmSound->bOverrideAttenuation = true;
	FSoundAttenuationSettings AttenuationSettings;
	AttenuationSettings.FalloffDistance = 400.f;
	FilmSound->AttenuationOverrides = AttenuationSettings;
}

void AERTV::BeginPlay()
{
	Super::BeginPlay();

#pragma region Nullchecks
	if (!FilmMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FilmMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!FilmMediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FilmMediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	FilmMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowWidgetOnScreen);
	FilmMediaPlayer->OpenSource(FilmMediaSource);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERTV::ShowWidgetOnScreen()
{
	UMaterialInstanceDynamic* DynamicMaterial{RootMesh->CreateDynamicMaterialInstance(1)};

#pragma region Nullchecks
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!TVScreenWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DynamicMaterial->SetTextureParameterValue(FName("Texture"), TVScreenWidget->GetRenderTarget());
}
