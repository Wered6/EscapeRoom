// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AERPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())};

#pragma region Nullchecks
	if (!MenuMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|MenuMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Subsystem is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Subsystem->AddMappingContext(MenuMappingContext, 0);
}

void AERPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(InputComponent)};

#pragma region Nullchecks
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnhancedInputComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	EnhancedInputComponent->BindAction(MenuPauseAction, ETriggerEvent::Started, this, &AERPlayerController::TriggerMenuPause);
}
