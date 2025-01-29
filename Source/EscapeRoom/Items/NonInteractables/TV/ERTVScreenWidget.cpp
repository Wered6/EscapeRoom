// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTVScreenWidget.h"
#include "ERTVScreenSignWidget.h"

void UERTVScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

#pragma region Nullchecks
	if (!TVScreenSignWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenSignWidgetClass is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	for (int i = 0; i < Password.Len() - 1; ++i)
	{
		
	}
}
