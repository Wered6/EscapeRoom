// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTV.h"

#include "ERTVScreenWidget.h"
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

	TVScreenWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TVScreenWidget"));
	TVScreenWidget->SetupAttachment(RootMesh);
	// Hide widget from screen in scene
	TVScreenWidget->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	TVScreenWidget->SetDrawSize(FVector2D(1440.f, 1440.f));

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

	// Comment out only for tests
	// FilmMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowWidgetOnScreen);
	// FilmMediaPlayer->OpenSource(FilmMediaSource);
}

void AERTV::EnterSignToPassword(const FString& Sign) const
{
	UERTVScreenWidget* ScreenWidget{Cast<UERTVScreenWidget>(TVScreenWidget->GetWidget())};

#pragma region Nullchecks
	if (!ScreenWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ScreenWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ScreenWidget->EnterSignToPassword(Sign);
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
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
	if (!TVScreenWidget->GetRenderTarget())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget->GetRenderTarget() is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DynamicMaterial->SetTextureParameterValue(FName("Texture"), TVScreenWidget->GetRenderTarget());
}
