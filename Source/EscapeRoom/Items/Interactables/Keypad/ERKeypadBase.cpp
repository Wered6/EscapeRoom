// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypadBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/RectLightComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "EscapeRoom/Components/ERInteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AERKeypadBase::AERKeypadBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh->SetCollisionProfileName("NoCollision");

	// Buttons
	Button0Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button0Mesh"));
	Button0Mesh->SetCollisionProfileName("NoCollision");
	Button0Mesh->SetupAttachment(RootMesh);
	Button1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button1Mesh"));
	Button1Mesh->SetCollisionProfileName("NoCollision");
	Button1Mesh->SetupAttachment(RootMesh);
	Button2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button2Mesh"));
	Button2Mesh->SetCollisionProfileName("NoCollision");
	Button2Mesh->SetupAttachment(RootMesh);
	Button3Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button3Mesh"));
	Button3Mesh->SetCollisionProfileName("NoCollision");
	Button3Mesh->SetupAttachment(RootMesh);
	Button4Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button4Mesh"));
	Button4Mesh->SetCollisionProfileName("NoCollision");
	Button4Mesh->SetupAttachment(RootMesh);
	Button5Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button5Mesh"));
	Button5Mesh->SetCollisionProfileName("NoCollision");
	Button5Mesh->SetupAttachment(RootMesh);
	Button6Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button6Mesh"));
	Button6Mesh->SetCollisionProfileName("NoCollision");
	Button6Mesh->SetupAttachment(RootMesh);
	Button7Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button7Mesh"));
	Button7Mesh->SetCollisionProfileName("NoCollision");
	Button7Mesh->SetupAttachment(RootMesh);
	Button8Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button8Mesh"));
	Button8Mesh->SetCollisionProfileName("NoCollision");
	Button8Mesh->SetupAttachment(RootMesh);
	Button9Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button9Mesh"));
	Button9Mesh->SetCollisionProfileName("NoCollision");
	Button9Mesh->SetupAttachment(RootMesh);
	ButtonDELMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonDELMesh"));
	ButtonDELMesh->SetCollisionProfileName("NoCollision");
	ButtonDELMesh->SetupAttachment(RootMesh);
	ButtonOKMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonOKMesh"));
	ButtonOKMesh->SetCollisionProfileName("NoCollision");
	ButtonOKMesh->SetupAttachment(RootMesh);

	ScrewL1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScrewL1Mesh"));
	ScrewL1Mesh->SetCollisionProfileName("NoCollision");
	ScrewL1Mesh->SetupAttachment(RootMesh);
	ScrewL2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScrewL2Mesh"));
	ScrewL2Mesh->SetCollisionProfileName("NoCollision");
	ScrewL2Mesh->SetupAttachment(RootMesh);
	ScrewR1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScrewR1Mesh"));
	ScrewR1Mesh->SetCollisionProfileName("NoCollision");
	ScrewR1Mesh->SetupAttachment(RootMesh);
	ScrewR2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScrewR2Mesh"));
	ScrewR2Mesh->SetCollisionProfileName("NoCollision");
	ScrewR2Mesh->SetupAttachment(RootMesh);
	ShieldLogoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldLogoMesh"));
	ShieldLogoMesh->SetCollisionProfileName("NoCollision");
	ShieldLogoMesh->SetupAttachment(RootMesh);

	// Led meshes
	GreenLedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenLedMesh"));
	GreenLedMesh->SetCollisionProfileName("NoCollision");
	GreenLedMesh->SetupAttachment(RootMesh);
	RedLedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedLedMesh"));
	RedLedMesh->SetCollisionProfileName("NoCollision");
	RedLedMesh->SetupAttachment(RootMesh);

	PlayerLocationScene = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerLocation"));
	PlayerLocationScene->SetupAttachment(RootMesh);
	PlayerLocationScene->SetRelativeLocation(FVector(0.f, -150.f, 30.f));

	HelpLight = CreateDefaultSubobject<URectLightComponent>(TEXT("HelpLight"));
	HelpLight->SetupAttachment(RootMesh);
	HelpLight->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	HelpLight->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	HelpLight->SetIntensityUnits(ELightUnits::Unitless);
	HelpLight->SetIntensity(5.f);
	HelpLight->SetAttenuationRadius(20.f);
	HelpLight->SetSourceWidth(8.f);
	HelpLight->SetSourceHeight(4.f);
	HelpLight->SetBarnDoorLength(1.f);

	OutlineMeshComponentPtr = RootMesh;
}

void AERKeypadBase::BeginPlay()
{
	Super::BeginPlay();

	PopulateButton2DArray();

	GreenLedDynMat = GreenLedMesh->CreateDynamicMaterialInstance(0);
	RedLedDynMat = RedLedMesh->CreateDynamicMaterialInstance(0);
}

void AERKeypadBase::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	EnterKeypadMode();

	UpdateSelectedButton();
}

void AERKeypadBase::EnterKeypadMode()
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadNavigateAction)
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

	AERCharacter* Character{Cast<AERCharacter>(InteractInstigator)};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const APlayerController* PlayerController{Character->GetController<APlayerController>()};

#pragma region Nullchecks
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	UEnhancedInputLocalPlayerSubsystem* Subsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())};
	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(PlayerController->InputComponent)};

#pragma region Nullchecks
	if (!Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Subsystem is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnhancedInputComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Subsystem->AddMappingContext(KeypadMappingContext, 0);
	EnhancedInputComponent->BindAction(KeypadNavigateAction, ETriggerEvent::Triggered, this, &AERKeypadBase::Navigate);
	EnhancedInputComponent->BindAction(KeypadButtonAction, ETriggerEvent::Started, this, &AERKeypadBase::ButtonPressed);
	EnhancedInputComponent->BindAction(KeypadButtonAction, ETriggerEvent::Completed, this, &AERKeypadBase::ButtonReleased);
	EnhancedInputComponent->BindAction(KeypadExitAction, ETriggerEvent::Triggered, this, &AERKeypadBase::Exit);

	LookAtKeypad();

	// IMC_Gameplay off
	Character->ExitGameplayInputMode();
	// No perform interaction check in Character so InteractableActor is set as Keypad
	Character->GetInteractComponent()->SetCanCheckInteraction(false);
	Character->SetIndicatorVisibility(false);
	// Turn off Widget and Outline but keep InteractableActor set as Keypad
	Execute_DisplayInteractionUI(this, false);
}

void AERKeypadBase::ExitKeypadMode() const
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!KeypadMappingContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|KeypadMappingContext is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	AERCharacter* Character{Cast<AERCharacter>(InteractInstigator)};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!SelectedButton.Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SelectedButton.Mesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const APlayerController* PlayerController{Character->GetController<APlayerController>()};

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

	Subsystem->RemoveMappingContext(KeypadMappingContext);

	Character->ResetCameraTransform();
	// IMC_Gameplay on
	Character->EnterGameplayInputMode();
	Character->GetInteractComponent()->SetCanCheckInteraction(false);
	Character->SetIndicatorVisibility(true);
	SelectedButton.Mesh->SetRenderCustomDepth(false);
	SelectedButton.Mesh->SetCustomDepthStencilValue(0);
}

void AERKeypadBase::LedFlash(const ELedColor LedColor, float FlashTime)
{
#pragma region Nullchecks
	if (!GreenLedDynMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|GreenLedDynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!RedLedDynMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|RedLedDynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ShortGreenLedSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ShortGreenLedSound is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ShortRedLedSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ShortRedLedSound is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LongGreenLedSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LongGreenLedSound is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LongRedLedSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LongRedLedSound is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	switch (LedColor)
	{
	case ELedColor::Green:
		// Set Emissive of Green Led
		GreenLedDynMat->SetScalarParameterValue(FName("Emissive"), 2.f);
	// Reset Emissive of Green Led after FlashTime
		GetWorldTimerManager().SetTimer(GreenLedEmiTimerHandle, [this]
		                                {
			                                GreenLedDynMat->SetScalarParameterValue(FName("Emissive"), 0.f);
		                                },
		                                FlashTime,
		                                false
		);
		UGameplayStatics::PlaySoundAtLocation(this, FlashTime == LedLongFlashTime ? LongGreenLedSound : ShortGreenLedSound, GetActorLocation());
		break;
	case ELedColor::Red:
		// Set Emissive of Red Led
		RedLedDynMat->SetScalarParameterValue(FName("Emissive"), 2.f);
	// Reset Emissive of Red Led after FlashTime
		GetWorldTimerManager().SetTimer(RedLedEmiTimerHandle, [this]
		                                {
			                                RedLedDynMat->SetScalarParameterValue(FName("Emissive"), 0.f);
		                                },
		                                FlashTime,
		                                false
		);
		UGameplayStatics::PlaySoundAtLocation(this, FlashTime == LedLongFlashTime ? LongRedLedSound : ShortRedLedSound, GetActorLocation());
		break;
	}
	// TODO add sounds for led flash
}

void AERKeypadBase::PopulateButton2DArray()
{
	FKeypadButton Button1{Button1Mesh, 1, EKeypadButtonValue::One}, Button2{Button2Mesh, 2, EKeypadButtonValue::Two}, Button3{Button3Mesh, 3, EKeypadButtonValue::Three};
	FKeypadButton Button4{Button4Mesh, 4, EKeypadButtonValue::Four}, Button5{Button5Mesh, 5, EKeypadButtonValue::Five}, Button6{Button6Mesh, 6, EKeypadButtonValue::Six};
	FKeypadButton Button7{Button7Mesh, 7, EKeypadButtonValue::Seven}, Button8{Button8Mesh, 8, EKeypadButtonValue::Eight}, Button9{Button9Mesh, 9, EKeypadButtonValue::Nine};
	FKeypadButton ButtonDEL{ButtonDELMesh, 10, EKeypadButtonValue::DEL}, Button0{Button0Mesh, 0, EKeypadButtonValue::Zero}, ButtonOK{ButtonOKMesh, 20, EKeypadButtonValue::OK};

	FKeypadButtonArray FirstRowButtons{Button1, Button2, Button3};
	FKeypadButtonArray SecondRowButtons{Button4, Button5, Button6};
	FKeypadButtonArray ThirdRowButtons{Button7, Button8, Button9};
	FKeypadButtonArray FourthRowButtons{ButtonDEL, Button0, ButtonOK};

	Button2DArray.Add(FirstRowButtons);
	Button2DArray.Add(SecondRowButtons);
	Button2DArray.Add(ThirdRowButtons);
	Button2DArray.Add(FourthRowButtons);
}

void AERKeypadBase::LookAtKeypad() const
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PlayerLocationScene)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerLocationScene is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const UCameraComponent* PlayerCamera{Cast<UCameraComponent>(InteractInstigator->GetComponentByClass(UCameraComponent::StaticClass()))};
	APlayerController* PlayerController{UGameplayStatics::GetPlayerController(this, 0)};

#pragma region Nullchecks
	if (!PlayerCamera)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerCamera is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerController is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Set player location XY of PlayerLocationScene XY
	FVector PlayerLocationXY{PlayerLocationScene->GetComponentLocation()};
	PlayerLocationXY.Z = InteractInstigator->GetActorLocation().Z;
	InteractInstigator->SetActorLocation(PlayerLocationXY);

	// Depends on bLookDirectlyAtKeypad look at keypad or in front of you
	const FVector LookAtVector{GetActorLocation()};
	FRotator CameraRotation;
	if (bLookDirectlyAtKeypad)
	{
		CameraRotation = UKismetMathLibrary::FindLookAtRotation(PlayerCamera->GetComponentLocation(), LookAtVector);
	}
	else
	{
		CameraRotation = PlayerLocationScene->GetForwardVector().Rotation();
		CameraRotation.Yaw += 90.f;
	}
	PlayerController->SetControlRotation(CameraRotation);
}

void AERKeypadBase::UpdateSelectedButton()
{
	if (!Button2DArray.IsValidIndex(Button2DArrayYIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Button2DArrayY is not valid index"), *FString(__FUNCTION__))
		return;
	}
	if (!Button2DArray[Button2DArrayYIndex].ButtonArray.IsValidIndex(Button2DArrayXIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Button2DArrayX is not valid index"), *FString(__FUNCTION__))
		return;
	}

	// Reset outline button if button is already selected
	if (SelectedButton.Mesh)
	{
		SelectedButton.Mesh->SetRenderCustomDepth(false);
		SelectedButton.Mesh->SetCustomDepthStencilValue(0);
	}

	SelectedButton = Button2DArray[Button2DArrayYIndex].ButtonArray[Button2DArrayXIndex];
	SelectedButton.Mesh->SetRenderCustomDepth(true);
	SelectedButton.Mesh->SetCustomDepthStencilValue(1);
}

void AERKeypadBase::StartProcessing()
{
	GetWorldTimerManager().SetTimer(LedBlinkTimerHandle, this, &AERKeypadBase::LedBlinking, LedBlinkInterval, true, 0.f);
}

void AERKeypadBase::LedBlinking()
{
	// Perform blink leds as many times as BlinkLoops counts
	if (LedBlinkLoopCounter++ < NumberOfBlinks)
	{
		LedFlash(ELedColor::Red, LedShortFlashTime);
		LedFlash(ELedColor::Green, LedShortFlashTime);
	}

	// End of blinking; greater not greater or equal to give one more loop without flashes
	if (LedBlinkLoopCounter > NumberOfBlinks)
	{
		GetWorldTimerManager().ClearTimer(LedBlinkTimerHandle);
		LedBlinkLoopCounter = 0;

		bCanNavigate = true;
		bCanPressButton = true;

		// Delegate
		if (OnFinishProcessing.IsBound())
		{
			OnFinishProcessing.Execute();
		}
	}
}

void AERKeypadBase::Navigate(const FInputActionValue& Value)
{
	if (!bCanNavigate)
	{
		return;
	}

	// Input is a Vector2D
	const FVector2D MovementVector{Value.Get<FVector2D>()};
	// Max length of buttons in keypad
	constexpr int MaxLoops{4};

	for (int i = 0; i < MaxLoops; ++i)
	{
		Button2DArrayXIndex += MovementVector.X;
		// Wrap limit 0 - 2
		Button2DArrayXIndex = Button2DArrayXIndex < 0 ? 2 : Button2DArrayXIndex > 2 ? 0 : Button2DArrayXIndex;

		Button2DArrayYIndex -= MovementVector.Y;
		// Wrap limit 0 - 3
		Button2DArrayYIndex = Button2DArrayYIndex < 0 ? 3 : Button2DArrayYIndex > 3 ? 0 : Button2DArrayYIndex;

		// If valid Mesh: break
		// else: loop
		if (Button2DArray[Button2DArrayYIndex].ButtonArray[Button2DArrayXIndex].Mesh->GetStaticMesh())
		{
			break;
		}
	}

	UpdateSelectedButton();
}

void AERKeypadBase::ButtonPressed()
{
	// TODO think about not blocking movement and pressing but maybe just dont do logic and flash and long sound on red led to show error
	if (!bCanPressButton)
	{
		return;
	}

	bCanNavigate = false;
	bCanPressButton = false;

	OnKeypadButtonPressed.Broadcast(SelectedButton.KeypadButtonValue, SelectedButton.Value);

	switch (SelectedButton.KeypadButtonValue)
	{
	case EKeypadButtonValue::Zero:
	case EKeypadButtonValue::One:
	case EKeypadButtonValue::Two:
	case EKeypadButtonValue::Three:
	case EKeypadButtonValue::Four:
	case EKeypadButtonValue::Five:
	case EKeypadButtonValue::Six:
	case EKeypadButtonValue::Seven:
	case EKeypadButtonValue::Eight:
	case EKeypadButtonValue::Nine:
		LedFlash(ELedColor::Green, LedShortFlashTime);
		break;
	case EKeypadButtonValue::DEL:
		LedFlash(ELedColor::Red, LedShortFlashTime);
		break;
	case EKeypadButtonValue::OK:
		if (bProcessing)
		{
			StartProcessing();
		}
		else
		{
			LedFlash(ELedColor::Green, LedShortFlashTime);
		}
		break;
	}

	PlayButtonAnimation();

	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonPressed"))
	// TODO add sound for clicking
	// TODO add think about delegates for number DEL and OK
}

void AERKeypadBase::ButtonReleased()
{
	// If button is OK, do not allow to navigate or press buttons
	// Navigate and pressing will reset after blinking led ends in StartLedBlinking()
	if (bProcessing)
	{
		bCanNavigate = SelectedButton.KeypadButtonValue != EKeypadButtonValue::OK;
		bCanPressButton = SelectedButton.KeypadButtonValue != EKeypadButtonValue::OK;
	}
	else
	{
		bCanNavigate = true;
		bCanPressButton = true;
	}

	ReverseButtonAnimation();

	UE_LOG(LogTemp, Warning, TEXT("KeypadButtonReleased"))
}

void AERKeypadBase::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("KeypadExit"))
	ExitKeypadMode();
	Execute_DisplayInteractionUI(this, true);
}
