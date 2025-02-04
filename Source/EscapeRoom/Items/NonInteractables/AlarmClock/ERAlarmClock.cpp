// Fill out your copyright notice in the Description page of Project Settings.


#include "ERAlarmClock.h"
#include "ERAlarmClockWidget.h"
#include "Components/WidgetComponent.h"
#include "Engine/TextureRenderTarget2D.h"


AERAlarmClock::AERAlarmClock()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);
	RootMesh->SetCollisionProfileName(TEXT("BlockAll"));

	AlarmClockWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("AlarmClockWidgetComp"));
	AlarmClockWidgetComp->SetupAttachment(RootMesh);
	// Hide widget from screen in scene
	AlarmClockWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 10000.f));
}

void AERAlarmClock::BeginPlay()
{
	Super::BeginPlay();
}


void AERAlarmClock::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AlarmClockScreenWidget = Cast<UERAlarmClockWidget>(AlarmClockWidgetComp->GetWidget());
}

void AERAlarmClock::ShowClock() const
{
	UMaterialInstanceDynamic* DynamicMaterial{RootMesh->CreateDynamicMaterialInstance(0)};

#pragma region Nullchecks
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!AlarmClockWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|AlarmClockWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!AlarmClockWidgetComp->GetRenderTarget())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|AlarmClockWidgetComp->GetRenderTarget() is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DynamicMaterial->SetTextureParameterValue(FName("Texture"), AlarmClockWidgetComp->GetRenderTarget());
}
