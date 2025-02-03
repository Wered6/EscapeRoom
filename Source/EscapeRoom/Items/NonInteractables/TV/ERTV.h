// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERTV.generated.h"

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
	// It's callable only for tests
	UFUNCTION(BlueprintCallable)
	void ShowHangmanWidgetOnScreen();

	UPROPERTY(EditAnywhere, Category="ER|TV|Hangman")
	FString Password{};
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Hangman")
	TObjectPtr<UWidgetComponent> TVScreenWidgetComp;
	UPROPERTY(VisibleAnywhere, Category="ER|TV|Hangman")
	TObjectPtr<UERTVScreenWidget> TVScreenWidget;

	UPROPERTY(VisibleAnywhere, Category="ER|TV|Components")
	TObjectPtr<UERKeyComponent> KeyComponent;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Film")
	TObjectPtr<UMediaSoundComponent> FilmSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Film")
	TObjectPtr<UMediaPlayer> FilmMediaPlayer;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Film")
	TObjectPtr<UFileMediaSource> FilmMediaSource;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;
};
