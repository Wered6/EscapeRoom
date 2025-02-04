// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERTV.generated.h"

class AERAlarmClock;
class UERKeyComponent;
class UFileMediaSource;
class UMediaPlayer;
class UMediaSoundComponent;
class UERTVScreenWidget;
class UWidgetComponent;

DECLARE_DELEGATE(FOnCorrectPassword)

UCLASS()
class ESCAPEROOM_API AERTV : public AActor
{
	GENERATED_BODY()

public:
	AERTV();

protected:
	virtual void BeginPlay() override;

public:
	bool EnterSignToPassword(const FString& Sign) const;

	FOnCorrectPassword OnCorrectPassword;

private:
	UFUNCTION()
	void StartAlarmClock();

	UFUNCTION()
	void ShowHangmanWidgetOnScreen();

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Alarm")
	TObjectPtr<AERAlarmClock> AlarmClock;

	UPROPERTY(EditAnywhere, Category="ER|TV|Hangman")
	FString Password{};

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Widget")
	TObjectPtr<UWidgetComponent> TVScreenWidgetComp;
	UPROPERTY(VisibleAnywhere, Category="ER|TV|Widget")
	TObjectPtr<UERTVScreenWidget> TVScreenWidget;

	UPROPERTY(VisibleAnywhere, Category="ER|TV|Components")
	TObjectPtr<UERKeyComponent> KeyComponent;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media")
	TObjectPtr<UMediaSoundComponent> FilmSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media")
	TObjectPtr<UMediaPlayer> FilmMediaPlayer;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Media")
	TObjectPtr<UFileMediaSource> FilmMediaSource;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;
};
