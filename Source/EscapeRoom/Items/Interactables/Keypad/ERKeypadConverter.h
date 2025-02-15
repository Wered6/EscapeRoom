// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadBase.h"
#include "ERKeypadConverter.generated.h"

class AERTV;

UCLASS()
class ESCAPEROOM_API AERKeypadConverter : public AERKeypadBase
{
	GENERATED_BODY()

public:
	AERKeypadConverter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void KeypadButtonPressed_Implementation() override;

private:
	UPROPERTY(EditInstanceOnly, Category="ER|KeypadTV")
	TObjectPtr<AERTV> TV;
};
