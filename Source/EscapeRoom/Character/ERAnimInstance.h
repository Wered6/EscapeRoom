// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ERAnimInstance.generated.h"

class AERFlashlight;
class AERCharacter;

UCLASS()
class ESCAPEROOM_API UERAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, Category=Character, meta=(AllowPrivateAccess="true"))
	TObjectPtr<AERCharacter> ERCharacter;

	UPROPERTY(BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	bool bHasFlashlight;

	UPROPERTY()
	TObjectPtr<AERFlashlight> EquippedFlashlight;

};
