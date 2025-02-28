// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "EscapeRoom/Components/ERInteractComponent.h"
#include "EscapeRoom/HUD/ERHUD.h"
#include "EscapeRoom/Items/Interactables/Flashlight/ERFlashlight.h"
#include "EscapeRoom/PlayerController/ERPlayerController.h"

AERCharacter::AERCharacter()
{
	// Try set to false
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

	InteractComponent = CreateDefaultSubobject<UERInteractComponent>(TEXT("InteractComponent"));

	CollectedUVGlasses.Add(FUVGlassData{FLinearColor(FColor::White), FLinearColor(FColor::White), 0.f});
}

void AERCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraDefaultTransform = Camera1P->GetRelativeTransform();

	// Intro with TV
	bLimitMovement = true;
	InteractComponent->SetCanCheckInteraction(false);
	SetIndicatorVisibility(false);
}

void AERCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

#pragma region Nullchecks
	if (!Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Controller is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	PlayerController = Cast<AERPlayerController>(Controller);

	EnterGameplayAndMenuInputMode();
}

void AERCharacter::SetLimitMovement(const bool bLimit)
{
	bLimitMovement = bLimit;
}

void AERCharacter::SetIndicatorVisibility(const bool bVisible) const
{
#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	AERHUD* HUD{Cast<AERHUD>(PlayerController->GetHUD())};

#pragma region Nullchecks
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|HUD is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	HUD->SetIndicatorVisibility(bVisible);
}

void AERCharacter::ResetCameraTransform() const
{
#pragma region Nullchecks
	if (!Camera1P)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Camera1P is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Camera1P->SetRelativeTransform(CameraDefaultTransform);
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
	if (!FlashlightChangeColorAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|FlashlightAction is nullptr"), *FString(__FUNCTION__))
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

	// Menu Pause
	EnhancedInputComponent->BindAction(PauseMenu, ETriggerEvent::Started, this, &AERCharacter::TriggerPauseMenu);

	// Gameplay Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AERCharacter::Move);

	// Gameplay Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AERCharacter::Look);

	// Gameplay Flashlight change color
	EnhancedInputComponent->BindAction(FlashlightChangeColorAction, ETriggerEvent::Started, this, &AERCharacter::UseFlashlight);
}

void AERCharacter::EnterGameplayAndMenuInputMode() const
{
#pragma region Nullchecks
	if (!GameplayMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DefaultMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
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

	Subsystem->AddMappingContext(MenuMappingContext, 0);
	Subsystem->AddMappingContext(GameplayMappingContext, 0);
}

void AERCharacter::EnterGameplayInputMode() const
{
#pragma region Nullchecks
	if (!GameplayMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|GameplayMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
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

	Subsystem->AddMappingContext(GameplayMappingContext, 0);
}

void AERCharacter::ExitGameplayInputMode() const
{
#pragma region Nullchecks
	if (!GameplayMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|GameplayMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
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

	Subsystem->RemoveMappingContext(GameplayMappingContext);
}

void AERCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D MovementVector{Value.Get<FVector2D>()};

	// Add movement to character
	if (!bLimitMovement)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AERCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector{Value.Get<FVector2D>()};

	// Add rotation to controller
	AddControllerPitchInput(LookAxisVector.Y);

	if (bLimitMovement)
	{
		const FRotator CurrentRotation{GetControlRotation()};
		if (CurrentRotation.Yaw >= 275.f && CurrentRotation.Yaw <= 340.f)
		{
			AddControllerYawInput(LookAxisVector.X);
		}
		else if (CurrentRotation.Yaw <= 275.f && LookAxisVector.X > 0.f)
		{
			AddControllerYawInput(LookAxisVector.X);
		}
		else if (CurrentRotation.Yaw >= 340.f && LookAxisVector.X < 0.f)
		{
			AddControllerYawInput(LookAxisVector.X);
		}
	}
	else
	{
		AddControllerYawInput(LookAxisVector.X);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::UseFlashlight()
{
	if (!EquippedFlashlight)
	{
		return;
	}

	if (CollectedUVGlasses.IsValidIndex(CollectedUVGlassesIndex))
	{
		EquippedFlashlight->TurnOn();
		EquippedFlashlight->SetUltraVioletColor(CollectedUVGlasses[CollectedUVGlassesIndex++]);
	}
	else
	{
		EquippedFlashlight->TurnOff();
		CollectedUVGlassesIndex = 0;
	}
}

void AERCharacter::EquipFlashlight(AERFlashlight* Flashlight)
{
	EquippedFlashlight = Flashlight;
	EquippedFlashlight->SetOwner(this);

	const USkeletalMeshSocket* HandSocket{Mesh1P->GetSocketByName(FName("RightHandSocket"))};

#pragma region Nullchecks
	if (!HandSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|HandSocket is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	HandSocket->AttachActor(EquippedFlashlight, Mesh1P);
}

void AERCharacter::CollectUVGlass(const FUVGlassData& UVGlassData)
{
	CollectedUVGlasses.Add(UVGlassData);
}
