// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadBase.h"
#include "ERKeypadHangman.generated.h"

class AERTV;

UCLASS()
class ESCAPEROOM_API AERKeypadHangman : public AERKeypadBase
{
	GENERATED_BODY()

public:
	AERKeypadHangman();

protected:
	virtual void BeginPlay() override;

public:
	void SendSignPasswordToTV();

protected:
	virtual void ButtonPressed() override;

private:
	void ExitAndDisableInteraction();

	UPROPERTY(EditInstanceOnly, Category="ER|KeypadHangman")
	TObjectPtr<AERTV> TV;

	uint8 Sign{};
};
