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
	virtual void Tick(float DeltaSeconds) override;

public:
	void StartClock();

private:
	UPROPERTY(EditAnywhere, Category="ER|AlarmClock|Time")
	uint8 Minutes{};
	UPROPERTY(EditAnywhere, Category="ER|AlarmClock|Time")
	uint8 Seconds{};
	float Timer{};
	bool bTimerOver{false};
	bool bStartTimer{false};

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> AlarmClockWidgetComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UERAlarmClockWidget> AlarmClockScreenWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> RootMesh;
};
