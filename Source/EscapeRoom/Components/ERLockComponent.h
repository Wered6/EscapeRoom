// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERLockComponent.generated.h"

DECLARE_DELEGATE(FOnUnlock)

/**
 * Component for items/objects that can be locked and with possibility to unlock (Items which have ERKeyComponent)
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ESCAPEROOM_API UERLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UERLockComponent();

protected:
	virtual void BeginPlay() override;

public:
	// TODO add sound for locking and unlocking things
	void Unlock();
	void Lock();

	UFUNCTION(BlueprintCallable, Category="ER|Lock")
	FORCEINLINE bool GetIsLocked() const
	{
		return bLocked;
	}

	FOnUnlock OnUnlock;

private:
	UPROPERTY(EditAnywhere, Category="ER|Lock")
	bool bLocked{true};
};
