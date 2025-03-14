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

protected:
	virtual void ButtonPressed() override;

private:
	void Convert();

	UPROPERTY(EditInstanceOnly, Category="ER|KeypadConverter")
	TObjectPtr<AERTV> TV;
};
