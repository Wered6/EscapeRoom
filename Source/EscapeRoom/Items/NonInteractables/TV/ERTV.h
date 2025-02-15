// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERTV.generated.h"

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

public:
	bool EnterSignToHangman(const FString& Sign) const;

	FOnCorrectHangmanPassword OnCorrectHangmanPassword;

	void SendNumberToConverter(const uint8 Number) const;
	bool NextRGBField() const;
	void ConvertRGBToHSV() const;

private:
	UFUNCTION()
	void StartAlarmClock();

	UFUNCTION()
	void ShowHangmanWidgetOnScreen();

	UFUNCTION()
	void ShowConverterWidgetOnScreen();

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Alarm")
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

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Intro")
	TObjectPtr<UMediaSoundComponent> IntroSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Intro")
	TObjectPtr<UMediaPlayer> IntroMediaPlayer;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media|Intro")
	TObjectPtr<UFileMediaSource> IntroMediaSource;

	UPROPERTY(VisibleAnywhere, Category="ER|TV|Components")
	TObjectPtr<UERKeyComponent> KeyComponent;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;
};
