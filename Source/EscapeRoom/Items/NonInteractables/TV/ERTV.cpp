// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTV.h"

#include "ERTVConverterScreenWidget.h"
#include "ERTVScreenSignWidget.h"
#include "ERTVScreenWidget.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "EscapeRoom/Components/ERKeyComponent.h"
#include "EscapeRoom/Items/NonInteractables/AlarmClock/ERAlarmClock.h"
#include "Runtime/MediaAssets/Public/MediaSoundComponent.h"


AERTV::AERTV()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("BlockAll"));

	HangmanWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HangmanWidgetComp"));
	HangmanWidgetComp->SetupAttachment(RootMesh);
	// Hide widget from screen in scene
	HangmanWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	HangmanWidgetComp->SetDrawSize(FVector2D(1440.f, 1440.f));

	ConverterWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ConverterWidgetComp"));
	ConverterWidgetComp->SetupAttachment(RootMesh);
	// Hide widget from screen in scene
	ConverterWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	ConverterWidgetComp->SetDrawSize(FVector2D(1440.f, 1440.f));

	IntroSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("FilmSound"));
	IntroSound->SetupAttachment(RootMesh);
	IntroSound->bAllowSpatialization = true;
	IntroSound->bOverrideAttenuation = true;
	FSoundAttenuationSettings AttenuationSettings;
	AttenuationSettings.FalloffDistance = 400.f;
	IntroSound->AttenuationOverrides = AttenuationSettings;

	KeyComponent = CreateDefaultSubobject<UERKeyComponent>(TEXT("KeyComponent"));
}

void AERTV::BeginPlay()
{
	Super::BeginPlay();

	HangmanWidget = Cast<UERTVScreenWidget>(HangmanWidgetComp->GetWidget());
	ConverterWidget = Cast<UERTVConverterScreenWidget>(ConverterWidgetComp->GetWidget());

	ScreenDynMat = RootMesh->CreateDynamicMaterialInstance(1);

#pragma region Nullchecks
	if (!HangmanWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!IntroMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FilmMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	HangmanWidget->Password = Password;

	// IntroMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowHangmanWidgetOnScreen);
	IntroMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowConverterWidgetOnScreen);
	IntroMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::StartAlarmClock);
	IntroMediaPlayer->OpenSource(IntroMediaSource);
}

bool AERTV::EnterSignToHangman(const FString& Sign) const
{
#pragma region Nullchecks
	if (!HangmanWidget)
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

	const bool CorrectSign{HangmanWidget->EnterSignToPassword(Sign)};
	if (HangmanWidget->Password == HangmanWidget->UserPassword)
	{
		KeyComponent->UnlockLockedItems();
		if (OnCorrectHangmanPassword.IsBound())
		{
			OnCorrectHangmanPassword.Execute();
			HangmanWidget->BravoWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	return CorrectSign;
}

void AERTV::SendNumberToConverter(const uint8 Number) const
{
#pragma region Nullchecks
	if (!ConverterWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ConverterWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ConverterWidget->UpdateCurrentRGBArrayElement(Number);
}

bool AERTV::NextRGBField() const
{
#pragma region Nullchecks
	if (!ConverterWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ConverterWidget is nullptr"), *FString(__FUNCTION__))
	}
#pragma endregion

	return ConverterWidget->NextRGBField();
}

void AERTV::ConvertRGBToHSV() const
{
#pragma region Nullchecks
	if (!ConverterWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ConverterWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ConverterWidget->Convert();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERTV::StartAlarmClock()
{
#pragma region Nullchecks
	if (!AlarmClock)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|AlarmClock is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	AlarmClock->StartClock();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERTV::ShowHangmanWidgetOnScreen()
{
#pragma region Nullchecks
	if (!ScreenDynMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!HangmanWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|HangmanWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!HangmanWidgetComp->GetRenderTarget())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|HangmanWidgetComp->GetRenderTarget() is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ScreenDynMat->SetTextureParameterValue(FName("Texture"), HangmanWidgetComp->GetRenderTarget());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERTV::ShowConverterWidgetOnScreen()
{
#pragma region Nullchecks
	if (!ScreenDynMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ScreenDynMat is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ConverterWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ConverterWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ConverterWidgetComp->GetRenderTarget())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ConverterWidgetComp->GetRenderTarget() is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ScreenDynMat->SetTextureParameterValue(FName("Texture"), ConverterWidgetComp->GetRenderTarget());
}
