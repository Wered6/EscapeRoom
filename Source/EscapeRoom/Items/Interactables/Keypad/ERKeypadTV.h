// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadBase.h"
#include "ERKeypadTV.generated.h"

class AERTV;

UCLASS()
class ESCAPEROOM_API AERKeypadTV : public AERKeypadBase
{
	GENERATED_BODY()

public:
	AERKeypadTV();

protected:
	virtual void BeginPlay() override;

public:
	virtual void KeypadButtonPressed_Implementation() override;

	void SendSignPasswordToTV();

private:
	void ExitAndDisableInteraction() const;

	UPROPERTY(EditInstanceOnly, Category="ER|KeypadTV")
	TObjectPtr<AERTV> TV;

	uint8 Sign{};
};
