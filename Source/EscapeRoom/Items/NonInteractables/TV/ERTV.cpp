// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTV.h"
#include "ERTVConverterScreenWidget.h"
#include "ERTVScreenSignWidget.h"
#include "ERTVScreenWidget.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "EscapeRoom/Components/ERKeyComponent.h"
#include "EscapeRoom/InteractionSystem/ERInteractComponent.h"
#include "EscapeRoom/Items/Interactables/Flashlight/ERFlashlight.h"
#include "EscapeRoom/Items/Interactables/Keypad/ERKeypadPassword.h"
#include "EscapeRoom/Items/NonInteractables/AlarmClock/ERAlarmClock.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
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

	TVSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("FilmSound"));
	TVSound->SetupAttachment(RootMesh);
	TVSound->bAllowSpatialization = true;
	TVSound->bOverrideAttenuation = true;
	FSoundAttenuationSettings AttenuationSettings;
	AttenuationSettings.FalloffDistance = 400.f;
	TVSound->AttenuationOverrides = AttenuationSettings;

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
	if (!Intro1MediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Intro1MediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!TVSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVSound is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!Flashlight)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Flashlight is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!Keypad)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Keypad is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	HangmanWidget->Password = Password;

	TVSound->SetMediaPlayer(TVMediaPlayer);
	// Uncomment after debugging
	OpenIntro1();

	Flashlight->OnFlashlightEquipped.BindUObject(this, &AERTV::OpenStage1);
	Keypad->OnCorrectPassword.BindUObject(this, &AERTV::OpenStage2);
}

void AERTV::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TVMediaPlayer->SetLooping(false);
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

void AERTV::ResetConverter() const
{
#pragma region Nullchecks
	if (!ConverterWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ConverterWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ConverterWidget->ResetRGBArrayIndex();
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

void AERTV::OpenIntro1()
{
#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TVMediaPlayer->OpenSource(Intro1MediaSource);
	TVMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::OpenIntro2);
}

void AERTV::OpenIntro2()
{
#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!Intro2MediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Intro2MediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TVMediaPlayer->OpenSource(Intro2MediaSource);
	TVMediaPlayer->OnEndReached.Clear();
	TVMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::OpenIntro3);
	TVMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::StartAlarmClock);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERTV::OpenIntro3()
{
	AERCharacter* ERCharacter{Cast<AERCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0))};

#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!NoSignalMediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|NoSignalMediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ERCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ERCharacter is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TVMediaPlayer->OpenSource(NoSignalMediaSource);
	TVMediaPlayer->OnEndReached.Clear();
	TVMediaPlayer->SetLooping(true);

	ERCharacter->SetLimitMovement(false);
	ERCharacter->SetIndicatorVisibility(true);
	ERCharacter->GetInteractComponent()->SetCanCheckInteraction(true);
}

void AERTV::OpenStage1()
{
#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!FlashlightClueMediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Stage1MediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	TVMediaPlayer->SetLooping(false);
	TVMediaPlayer->OpenSource(FlashlightClueMediaSource);
	TVMediaPlayer->OnEndReached.Clear();
	TVMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowConverterWidgetOnScreen);
}

void AERTV::OpenStage2()
{
#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PasswordClueMediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PasswordClueMediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!TVMediaTexture)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaTexture is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ScreenDynMat->SetTextureParameterValue(FName("Texture"), TVMediaTexture);

	TVMediaPlayer->OpenSource(PasswordClueMediaSource);
	TVMediaPlayer->OnEndReached.Clear();
	TVMediaPlayer->OnEndReached.AddDynamic(this, &AERTV::ShowHangmanWidgetOnScreen);
}

void AERTV::OpenToBeContinued()
{
#pragma region Nullchecks
	if (!TVMediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVMediaPlayer is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ToBeContinuedMediaSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ToBeContinuedMediaSource is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ScreenDynMat->SetTextureParameterValue(FName("Texture"), TVMediaTexture);

	TVMediaPlayer->OpenSource(ToBeContinuedMediaSource);
}
