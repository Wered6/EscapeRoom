// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERTV.generated.h"

class UFileMediaSource;
class UMediaPlayer;
class UMediaSoundComponent;
class UERTVScreenWidget;
class UWidgetComponent;

UCLASS()
class ESCAPEROOM_API AERTV : public AActor
{
	GENERATED_BODY()

public:
	AERTV();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ShowWidgetOnScreen();

	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Widget")
	TObjectPtr<UWidgetComponent> TVScreenWidget;

	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Film")
	TObjectPtr<UMediaSoundComponent> FilmSound;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Film")
	TObjectPtr<UMediaPlayer> FilmMediaPlayer;
	UPROPERTY(EditDefaultsOnly, Category="ER|TV|Film")
	TObjectPtr<UFileMediaSource> FilmMediaSource;
};
