// Fill out your copyright notice in the Description page of Project Settings.


#include "ERCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "EscapeRoom/HUD/ERHUD.h"
#include "EscapeRoom/Items/Interactables/Flashlight/ERFlashlight.h"
#include "EscapeRoom/Items/Interactables/Keypad/ERKeypadInteface.h"
#include "EscapeRoom/PlayerController/ERPlayerController.h"

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

	CameraDefaultTransform = Camera1P->GetRelativeTransform();
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

void AERCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PerformInteractionCheck();
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
	if (!InteractAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadMoveAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadMoveAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadButtonAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadButtonAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadExitAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadExitAction is nullptr"), *FString(__FUNCTION__))
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
	EnhancedInputComponent->BindAction(FlashlightChangeColorAction, ETriggerEvent::Started, this, &AERCharacter::FlashlightChangeColorButtonPressed);

	// Gameplay Interact
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AERCharacter::Interact);

	// Keypad Moving
	EnhancedInputComponent->BindAction(KeypadMoveAction, ETriggerEvent::Triggered, this, &AERCharacter::KeypadMove);

	// Keypad Accept button pressed
	EnhancedInputComponent->BindAction(KeypadButtonAction, ETriggerEvent::Started, this, &AERCharacter::KeypadButtonPressed);

	// Keypad Accept button released
	EnhancedInputComponent->BindAction(KeypadButtonAction, ETriggerEvent::Completed, this, &AERCharacter::KeypadButtonReleased);

	// Keypad Exit
	EnhancedInputComponent->BindAction(KeypadExitAction, ETriggerEvent::Started, this, &AERCharacter::KeypadExit);
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

void AERCharacter::EnterKeypadInputMode() const
{
#pragma region Nullchecks
	if (!GameplayMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|GameplayMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadMappingContext is nullptr"), *FString(__FUNCTION__))
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
	Subsystem->AddMappingContext(KeypadMappingContext, 0);
}

void AERCharacter::ExitKeypadInputMode() const
{
#pragma region Nullchecks
	if (!KeypadMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
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

	Subsystem->RemoveMappingContext(KeypadMappingContext);
	Subsystem->AddMappingContext(GameplayMappingContext, 0);
}

void AERCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D MovementVector{Value.Get<FVector2D>()};

	// Add movement to character
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AERCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector{Value.Get<FVector2D>()};

	// Add rotation to controller
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::FlashlightChangeColorButtonPressed()
{
	if (!EquippedFlashlight)
	{
		return;
	}

	EquippedFlashlight->SwitchToNextColor();
#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	PlayerController->OutlineUltraVioletColor(EquippedFlashlight->GetCurrentColor());
}

void AERCharacter::Interact()
{
	// Return if no interactable actor found
	if (!InteractableActor)
	{
		return;
	}

	// If interactable actor has interact interface fire interact start function
	if (InteractableActor->Implements<UERInteractInterface>())
	{
		IERInteractInterface::Execute_InteractStart(InteractableActor, this);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::KeypadMove(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D MovementVector{Value.Get<FVector2D>()};

#pragma region Nullchecks
	if (!InteractableActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractableActor is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// If interactable actor has keypad interface fire keypad move function
	if (InteractableActor->Implements<UERKeypadInterface>())
	{
		IERKeypadInterface::Execute_KeypadMove(InteractableActor, MovementVector);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::KeypadButtonPressed()
{
#pragma region Nullchecks
	if (!InteractableActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractableActor is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// If interactable actor has keypad interface fire keypad move function
	if (InteractableActor->Implements<UERKeypadInterface>())
	{
		IERKeypadInterface::Execute_KeypadButtonPressed(InteractableActor);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::KeypadButtonReleased()
{
#pragma region Nullchecks
	if (!InteractableActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractableActor is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// If interactable actor has keypad interface fire keypad move function
	if (InteractableActor->Implements<UERKeypadInterface>())
	{
		IERKeypadInterface::Execute_KeypadButtonReleased(InteractableActor);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AERCharacter::KeypadExit()
{
#pragma region Nullchecks
	if (!InteractableActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractableActor is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// If interactable actor has keypad interface fire keypad move function
	if (InteractableActor->Implements<UERKeypadInterface>())
	{
		IERKeypadInterface::Execute_KeypadExit(InteractableActor);
	}
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

void AERCharacter::PerformInteractionCheck()
{
	if (!bCanCheckInteraction)
	{
		return;
	}

#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Get camera location and direction
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Define the start and end points of the line trace
	const FVector Start{CameraLocation};
	const FVector End{Start + CameraRotation.Vector() * InteractionDistance};

	// Perform the line trace
	FHitResult HitResult;
	const bool bHit{
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility
		)
	};

	// If nothing was hit, reset interaction and return
	if (!bHit)
	{
		ClearInteraction();
		return;
	}

	AActor* HitActor{HitResult.GetActor()};
	UPrimitiveComponent* HitComponent{HitResult.GetComponent()};

	// If hitting the same interactable component, do nothing and return
	if (HitComponent == InteractableHitComponent)
	{
		return;
	}

	// If previously interacting with something else, hide its UI
	if (InteractableActor)
	{
		IERInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
	}

	// Check if the hit actor implements the interact interface and has correct collision
	if (HitActor->Implements<UERInteractInterface>() && HitComponent->GetCollisionProfileName() == FName("InteractArea"))
	{
		IERInteractInterface::Execute_DisplayInteractionUI(HitActor, true);
		InteractableActor = HitActor;
		InteractableHitComponent = HitComponent;
	}
	else
	{
		ClearInteraction();
	}
}

void AERCharacter::ClearInteraction()
{
	if (InteractableActor)
	{
		IERInteractInterface::Execute_DisplayInteractionUI(InteractableActor, false);
	}
	InteractableActor = nullptr;
	InteractableHitComponent = nullptr;
}

void AERCharacter::EquipFlashlight(AERFlashlight* Flashlight)
{
	EquippedFlashlight = Flashlight;

#pragma region Nullchecks
	if (!EquippedFlashlight)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EquippedFlashlight is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	EquippedFlashlight->SetOwner(this);
	PlayerController->AddToViewportFlashlightWidget();

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
