// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERAlarmClock.generated.h"

class UERAlarmClockWidget;
class UWidgetComponent;

UCLASS()
class ESCAPEROOM_API AERAlarmClock : public AActor
{
	GENERATED_BODY()

public:
	AERAlarmClock();

protected:
	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;

	void ShowClock() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="ER|AlarmClock|Time")
	TObjectPtr<UWidgetComponent> AlarmClockWidgetComp;
	UPROPERTY(VisibleAnywhere, Category="ER|AlarmClock|Time")
	TObjectPtr<UERAlarmClockWidget> AlarmClockScreenWidget;

	UPROPERTY(EditDefaultsOnly, Category="ER|AlarmClock|Mesh")
	TObjectPtr<UStaticMeshComponent> RootMesh;
};
