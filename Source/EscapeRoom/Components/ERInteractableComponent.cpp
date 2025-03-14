// Fill out your copyright notice in the Description page of Project Settings.


#include "ERInteractableComponent.h"
#include "Components/WidgetComponent.h"
#include "EscapeRoom/UI/ERInteractIconWidget.h"


UERInteractableComponent::UERInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	UPrimitiveComponent::SetCollisionProfileName(TEXT("InteractArea"));

	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	InteractWidgetComp->SetDrawAtDesiredSize(true);
	InteractWidgetComp->SetVisibility(false);
}

void UERInteractableComponent::OnRegister()
{
	Super::OnRegister();

#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidgetComp->SetupAttachment(GetOwner()->GetRootComponent());
}

void UERInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

#pragma region Nullchecks
	if (!InteractWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetClass is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidget = CreateWidget<UERInteractIconWidget>(GetWorld(), InteractWidgetClass);

#pragma region Nullchecks
	if (!InteractWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidget is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidget->Init(InteractCategory, InteractType, 0.f, FVector2D(100.f, 100.f), FVector2D(100.f, 100.f));
	InteractWidgetComp->SetWidget(InteractWidget);
}

void UERInteractableComponent::SetCanInteract(const bool bCanInteract)
{
	SetCollisionProfileName(bCanInteract ? TEXT("InteractArea") : TEXT("NoCollision"));
}

void UERInteractableComponent::SetShowInteractWidget(const bool bShow) const
{
#pragma region Nullchecks
	if (!InteractWidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractWidgetComp is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	InteractWidgetComp->SetVisibility(bShow);
}
