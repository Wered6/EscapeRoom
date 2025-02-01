// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERKeyComponent.generated.h"


/**
 * Component for items/objects that can unlock locked items (Items which have ERLockComponent)
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ESCAPEROOM_API UERKeyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UERKeyComponent();

protected:
	virtual void BeginPlay() override;

public:
	/**
	 * Unlocking all locked items in LockedItems array
	 */
	void UnlockLockedItems();

private:
	void PopulateLockedItemsFromTags();

	/**
	 * Use for simple "many keys - one locked item"
	 */
	UPROPERTY(EditInstanceOnly, Category="ER|Key")
	TArray<AActor*> LockedItems;
	/**
	 * Use for complex "many keys - many locked items" (just mark more items with same Tag) or actor with children like Cabinet.
	 * If LockedChildTag is empty, it wil search only through LockedParentTag
	 */
	UPROPERTY(EditAnywhere, Category="ER|Key")
	FName LockedParentTag{};
	/**
	 * If LockedParentTag is empty, it will use no tags anyway
	 */
	UPROPERTY(EditAnywhere, Category="ER|Key")
	FName LockedChildTag{};
};
