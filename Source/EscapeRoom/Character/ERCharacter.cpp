// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "EscapeRoom/Flashlight/Flashlight.h"

AERCharacter::AERCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	// Create CameraComponent
	Camera1P = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1P"));
	Camera1P->SetupAttachment(GetCapsuleComponent());
	Camera1P->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	Camera1P->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(Camera1P);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-4.f, 0.f, -150.f));
}

void AERCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AERCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AERCharacter::SetOverlappingFlashlight(AFlashlight* Flashlight)
{
	// If already overlaps some flashlight, turn off their pickup widget
	if (OverlappingFlashlight)
	{
		OverlappingFlashlight->ShowPickupWidget(false);
	}
	OverlappingFlashlight = Flashlight;
	// If there is new flashlight turn on their pickup widget
	if (OverlappingFlashlight)
	{
		OverlappingFlashlight->ShowPickupWidget(true);
	}
}

void AERCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (!Controller)
	{
		return;
	}

#pragma region Nullchecks
	if (!DefaultMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DefaultMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Add input Mapping Context
	const APlayerController* PlayerController{Cast<APlayerController>(Controller)};

#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())};

#pragma region Nullchecks
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Subsystem is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AERCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
#pragma region Nullchecks
	if (!MoveAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|MoveAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LookAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LookAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!EquipAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EquipAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(PlayerInputComponent)};

#pragma region Nullchecks
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnhancedInputComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AERCharacter::Move);

	// Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AERCharacter::Look);

	// Equip
	EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AERCharacter::EquipButtonPressed);
}

void AERCharacter::Move(const FInputActionValue& Value)
{
#pragma region Nullchecks
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Controller is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Input is a Vector2D
	const FVector2D MovementVector{Value.Get<FVector2D>()};

	// Add movement
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AERCharacter::Look(const FInputActionValue& Value)
{
#pragma region Nullchecks
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Controller is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Input is a Vector2D
	const FVector2D LookAxisVector{Value.Get<FVector2D>()};

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AERCharacter::EquipButtonPressed()
{
	if (!OverlappingFlashlight)
	{
		return;
	}

#pragma region Nullchecks
	if (!Mesh1P)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Mesh1P is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	EquippedFlashlight = OverlappingFlashlight;
	EquippedFlashlight->SetIsEquipped();
	const USkeletalMeshSocket* HandSocket{Mesh1P->GetSocketByName(FName("RightHandSocket"))};

#pragma region Nullchecks
	if (!HandSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|HandSocket is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	HandSocket->AttachActor(EquippedFlashlight, Mesh1P);
	EquippedFlashlight->SetOwner(this);
	EquippedFlashlight->ShowPickupWidget(false);
	EquippedFlashlight->GetPickUpSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
