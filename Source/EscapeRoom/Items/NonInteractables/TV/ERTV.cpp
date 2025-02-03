// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTV.h"
#include "ERTVScreenSignWidget.h"
#include "ERTVScreenWidget.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "EscapeRoom/Components/ERKeyComponent.h"
#include "Runtime/MediaAssets/Public/MediaSoundComponent.h"


AERTV::AERTV()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("NoCollision"));

	TVScreenWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("TVScreenWidgetComp"));
	TVScreenWidgetComp->SetupAttachment(RootMesh);
	// Hide widget from screen in scene
	TVScreenWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	TVScreenWidgetComp->SetDrawSize(FVector2D(1440.f, 1440.f));

	FilmSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("FilmSound"));
	FilmSound->SetupAttachment(RootMesh);
	FilmSound->bAllowSpatialization = true;
	FilmSound->bOverrideAttenuation = true;
	FSoundAttenuationSettings AttenuationSettings;
	AttenuationSettings.FalloffDistance = 400.f;
	FilmSound->AttenuationOverrides = AttenuationSettings;

	KeyComponent = CreateDefaultSubobject<UERKeyComponent>(TEXT("KeyComponent"));
}

void AERTV::BeginPlay()
{
	Super::BeginPlay();

	TVScreenWidget = Cast<UERTVScreenWidget>(TVScreenWidgetComp->GetWidget());

#pragma region Nullchecks
	if (!TVScreenWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TVScreenWidget->Password = Password;

	// Comment out only for tests
	// FilmMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowWidgetOnScreen);
	// FilmMediaPlayer->OpenSource(FilmMediaSource);
}

bool AERTV::EnterSignToPassword(const FString& Sign) const
{
#pragma region Nullchecks
	if (!TVScreenWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget is nullptr"), *FString(__FUNCTION__))
		return false;
	}
	if (!KeyComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeyComponent is nullptr"), *FString(__FUNCTION__))
		return false;
	}
#pragma endregion

	const bool CorrectSign{TVScreenWidget->EnterSignToPassword(Sign)};
	if (TVScreenWidget->Password == TVScreenWidget->UserPassword)
	{
		KeyComponent->UnlockLockedItems();
		if (OnCorrectPassword.IsBound())
		{
			OnCorrectPassword.Execute();
			TVScreenWidget->BravoWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	return CorrectSign;
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void AERTV::ShowHangmanWidgetOnScreen()
{
	UMaterialInstanceDynamic* DynamicMaterial{RootMesh->CreateDynamicMaterialInstance(1)};

#pragma region Nullchecks
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!TVScreenWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!TVScreenWidgetComp->GetRenderTarget())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget->GetRenderTarget() is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DynamicMaterial->SetTextureParameterValue(FName("Texture"), TVScreenWidgetComp->GetRenderTarget());
}
