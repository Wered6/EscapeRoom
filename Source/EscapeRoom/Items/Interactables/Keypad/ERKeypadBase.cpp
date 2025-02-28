// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypadBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/RectLightComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "EscapeRoom/Components/ERInteractComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


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

	// Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootMesh);
	SpringArm->TargetArmLength = 50.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

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
}

void AERKeypadBase::EnterKeypadMode()
{
	APlayerController* PlayerController{UGameplayStatics::GetPlayerController(this, 0)};
	AERCharacter* Character{Cast<AERCharacter>(InteractInstigator)};

#pragma region Nullchecks
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
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
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

	Subsystem->AddMappingContext(KeypadMappingContext, 1);

	Character->GetInteractComponent()->SetCanCheckInteraction(false);
	Character->SetIndicatorVisibility(false);
	Execute_DisplayInteractionUI(this, false);
	PlayerController->Possess(this);

	UpdateSelectedButton();
}

void AERKeypadBase::ExitKeypadMode() const
{
	APlayerController* PlayerController{UGameplayStatics::GetPlayerController(this, 0)};
	AERCharacter* Character{Cast<AERCharacter>(InteractInstigator)};

#pragma region Nullchecks
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
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
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

	Character->GetInteractComponent()->SetCanCheckInteraction(true);
	Character->SetIndicatorVisibility(true);
	PlayerController->Possess(Cast<APawn>(InteractInstigator));

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

void AERKeypadBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent{Cast<UEnhancedInputComponent>(PlayerInputComponent)};

#pragma region Nullchecks
	if (!NavigateAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|NavigateAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ButtonAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ButtonAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!ExitAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|ExitAction is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnhancedInputComponent is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	EnhancedInputComponent->BindAction(NavigateAction, ETriggerEvent::Triggered, this, &AERKeypadBase::Navigate);
	EnhancedInputComponent->BindAction(ButtonAction, ETriggerEvent::Started, this, &AERKeypadBase::ButtonPressed);
	EnhancedInputComponent->BindAction(ButtonAction, ETriggerEvent::Completed, this, &AERKeypadBase::ButtonReleased);
	EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Triggered, this, &AERKeypadBase::Exit);
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
