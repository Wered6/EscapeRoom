// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERTV.generated.h"

class AERKeypadPassword;
class UMediaTexture;
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
	TObjectPtr<AERKeypadPassword> Keypad;

	UPROPERTY(EditInstanceOnly, Category="ER|TV|Flashlight")
	TObjectPtr<AERFlashlight> Flashlight;

	UPROPERTY(EditInstanceOnly, Category="ER|TV|Alarm")
	TObjectPtr<AERAlarmClock> AlarmClock;

	UPROPERTY(EditAnywhere, Category="ER|TV|Hangman")
	FString Password{};
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HangmanWidgetComp;
	UPROPERTY()
	TObjectPtr<UERTVScreenWidget> HangmanWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> ConverterWidgetComp;
	UPROPERTY()
	TObjectPtr<UERTVConverterScreenWidget> ConverterWidget;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> ScreenDynMat;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERKeyComponent> KeyComponent;

	UPROPERTY(VisibleAnywhere)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ER|TV|Media", meta=(AllowPrivateAccess=true))
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
