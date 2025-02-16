// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERTV.generated.h"

class UMediaTexture;
class AERKeypad;
class AERFlashlight;
class UERTVConverterScreenWidget;
class AERAlarmClock;
class UERKeyComponent;
class UFileMediaSource;
class UMediaPlayer;
class UMediaSoundComponent;
class UERTVScreenWidget;
class UWidgetComponent;

DECLARE_DELEGATE(FOnCorrectHangmanPassword)

UCLASS()
class ESCAPEROOM_API AERTV : public AActor
{
	GENERATED_BODY()

public:
	AERTV();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	bool EnterSignToHangman(const FString& Sign) const;

	FOnCorrectHangmanPassword OnCorrectHangmanPassword;

	void SendNumberToConverter(const uint8 Number) const;
	bool NextRGBField() const;
	void ConvertRGBToHSV() const;
	void ResetConverter() const;

private:
	UFUNCTION()
	void StartAlarmClock();

	UFUNCTION()
	void ShowHangmanWidgetOnScreen();

	UFUNCTION()
	void ShowConverterWidgetOnScreen();

	UPROPERTY(EditInstanceOnly, Category="ER|TV|Keypad")
	TObjectPtr<AERKeypad> Keypad;

	UPROPERTY(EditInstanceOnly, Category="ER|TV|Flashlight")
	TObjectPtr<AERFlashlight> Flashlight;

	UPROPERTY(EditInstanceOnly, Category="ER|TV|Alarm")
	TObjectPtr<AERAlarmClock> AlarmClock;

	UPROPERTY(EditAnywhere, Category="ER|TV|Hangman")
	FString Password{};
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Hangman")
	TObjectPtr<UWidgetComponent> HangmanWidgetComp;
	UPROPERTY(VisibleAnywhere, Category="ER|TV|Hangman")
	TObjectPtr<UERTVScreenWidget> HangmanWidget;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Converter")
	TObjectPtr<UWidgetComponent> ConverterWidgetComp;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Converter")
	TObjectPtr<UERTVConverterScreenWidget> ConverterWidget;

	UPROPERTY(VisibleAnywhere, Category="ER|TV|Screen")
	TObjectPtr<UMaterialInstanceDynamic> ScreenDynMat;

	UPROPERTY(VisibleAnywhere, Category="ER|TV|Components")
	TObjectPtr<UERKeyComponent> KeyComponent;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

#pragma region Movies

private:
	void OpenIntro1();
	UFUNCTION()
	void OpenIntro2();
	UFUNCTION()
	void OpenIntro3();
	UFUNCTION()
	void OpenStage1();
	UFUNCTION()
	void OpenStage2();
	UFUNCTION(BlueprintCallable)
	void OpenToBeContinued();

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media")
	TObjectPtr<UMediaPlayer> TVMediaPlayer;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media")
	TObjectPtr<UMediaTexture> TVMediaTexture;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Intro")
	TObjectPtr<UFileMediaSource> Intro1MediaSource;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Intro")
	TObjectPtr<UFileMediaSource> Intro2MediaSource;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Intro")
	TObjectPtr<UFileMediaSource> NoSignalMediaSource;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Stage1")
	TObjectPtr<UFileMediaSource> FlashlightClueMediaSource;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Stage2")
	TObjectPtr<UFileMediaSource> PasswordClueMediaSource;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|TBC")
	TObjectPtr<UFileMediaSource> ToBeContinuedMediaSource;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Sound")
	TObjectPtr<UMediaSoundComponent> TVSound;

#pragma endregion
};
