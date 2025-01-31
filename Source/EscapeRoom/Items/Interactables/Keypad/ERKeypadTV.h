// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadBase.h"
#include "ERKeypadTV.generated.h"

UCLASS()
class ESCAPEROOM_API AERKeypadTV : public AERKeypadBase
{
	GENERATED_BODY()

public:
	AERKeypadTV();

protected:
	virtual void BeginPlay() override;
};
