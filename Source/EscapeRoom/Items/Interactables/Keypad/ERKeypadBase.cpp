// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypadBase.h"
#include "Camera/CameraComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AERKeypadBase::AERKeypadBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh->SetCollisionProfileName("NoCollision");

	// Buttons
	ButtonOneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonOneMesh"));
	ButtonOneMesh->SetCollisionProfileName("NoCollision");
	ButtonOneMesh->SetupAttachment(RootMesh);
	ButtonTwoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonTwoMesh"));
	ButtonTwoMesh->SetCollisionProfileName("NoCollision");
	ButtonTwoMesh->SetupAttachment(RootMesh);
	ButtonThreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonThreeMesh"));
	ButtonThreeMesh->SetCollisionProfileName("NoCollision");
	ButtonThreeMesh->SetupAttachment(RootMesh);
	ButtonFourMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonFourMesh"));
	ButtonFourMesh->SetCollisionProfileName("NoCollision");
	ButtonFourMesh->SetupAttachment(RootMesh);
	ButtonFiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonFiveMesh"));
	ButtonFiveMesh->SetCollisionProfileName("NoCollision");
	ButtonFiveMesh->SetupAttachment(RootMesh);
	ButtonSixMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonSixMesh"));
	ButtonSixMesh->SetCollisionProfileName("NoCollision");
	ButtonSixMesh->SetupAttachment(RootMesh);
	ButtonSevenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonSevenMesh"));
	ButtonSevenMesh->SetCollisionProfileName("NoCollision");
	ButtonSevenMesh->SetupAttachment(RootMesh);
	ButtonEightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonEightMesh"));
	ButtonEightMesh->SetCollisionProfileName("NoCollision");
	ButtonEightMesh->SetupAttachment(RootMesh);
	ButtonNineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonNineMesh"));
	ButtonNineMesh->SetCollisionProfileName("NoCollision");
	ButtonNineMesh->SetupAttachment(RootMesh);
	ButtonDelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonDelMesh"));
	ButtonDelMesh->SetCollisionProfileName("NoCollision");
	ButtonDelMesh->SetupAttachment(RootMesh);
	ButtonZeroMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonZeroMesh"));
	ButtonZeroMesh->SetCollisionProfileName("NoCollision");
	ButtonZeroMesh->SetupAttachment(RootMesh);
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

void AERKeypadBase::KeypadMove_Implementation(const FVector2D& MovementVector)
{
	if (!bCanNavigate)
	{
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		Button2DArrayX += MovementVector.X;
		// Wrap limit 0 - 2
		Button2DArrayX = Button2DArrayX < 0 ? 2 : Button2DArrayX > 2 ? 0 : Button2DArrayX;

		Button2DArrayY -= MovementVector.Y;
		// Wrap limit 0 - 3
		Button2DArrayY = Button2DArrayY < 0 ? 3 : Button2DArrayY > 3 ? 0 : Button2DArrayY;

		// If valid Mesh break, else loop
		if (Button2DArray[Button2DArrayY].ButtonArray[Button2DArrayX].Mesh->GetStaticMesh())
		{
			break;
		}
	}

	UpdateSelectedButton();
}

void AERKeypadBase::KeypadButtonPressed_Implementation()
{
	// TODO think about not blocking movement and pressing but maybe just dont do logic and flash and long sound on red led to show error
	if (!bCanPressButton)
	{
		return;
	}

	bCanNavigate = false;
	bCanPressButton = false;

	// All buttons except DEL and OK
	if (SelectedButton.Value < 10)
	{
		LedFlash(ELedColor::Green, LedShortFlashTime);
	}
	// DEL/OK
	else
	{
		// If DEL
		if (SelectedButton.Value == 10)
		{
			LedFlash(ELedColor::Red, LedShortFlashTime);
		}
		// If OK
		else if (SelectedButton.Value == 20)
		{
			StartLedBlinking();
		}
	}

	PlayButtonAnimation();

	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonPressed"))
	// TODO add sound for clicking
}

void AERKeypadBase::KeypadButtonReleased_Implementation()
{
	// If button is OK, do not allow to navigate or press buttons
	// Navigate and pressing will reset after blinking led ends in StartLedBlinking()
	bCanNavigate = SelectedButton.Value != 20;
	bCanPressButton = SelectedButton.Value != 20;

	ReverseButtonAnimation();

	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonReleased"))
}

void AERKeypadBase::KeypadExit_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("KeypadExit"))
	EnterDefaultMode();
	Execute_DisplayInteractionUI(this, true);
}

void AERKeypadBase::EnterKeypadMode()
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	LookAtKeypad();

	AERCharacter* Character{Cast<AERCharacter>(InteractInstigator)};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// IMC_Default off IMC_Keypad on
	Character->EnterKeypadInputMode();
	// No perform interaction check in Character so InteractableActor is set as Keypad
	Character->SetCanCheckInteraction(false);
	Character->SetIndicatorVisibility(false);
	// Turn off Widget and Outline but keep InteractableActor set as Keypad
	Execute_DisplayInteractionUI(this, false);
}

void AERKeypadBase::EnterDefaultMode() const
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
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

	Character->ResetCameraTransform();
	// IMD_Default on IMC_Keypad off
	Character->EnterDefaultInputMode();
	Character->SetCanCheckInteraction(true);
	Character->SetIndicatorVisibility(true);
	SelectedButton.Mesh->SetOverlayMaterial(nullptr);
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
		break;
	}
	// TODO add sounds for led flash
}

void AERKeypadBase::PopulateButton2DArray()
{
	FKeypadButton Button1{ButtonOneMesh, 1}, Button2{ButtonTwoMesh, 2}, Button3{ButtonThreeMesh, 3};
	FKeypadButton Button4{ButtonFourMesh, 4}, Button5{ButtonFiveMesh, 5}, Button6{ButtonSixMesh, 6};
	FKeypadButton Button7{ButtonSevenMesh, 7}, Button8{ButtonEightMesh, 8}, Button9{ButtonNineMesh, 9};
	FKeypadButton ButtonDEL{ButtonDelMesh, 10}, Button0{ButtonZeroMesh, 0}, ButtonOK{ButtonOKMesh, 20};

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

	// Set camera rotation so player will look ay keypad
	const FVector LookAtVector{GetActorLocation()};
	const FRotator CameraRotation{UKismetMathLibrary::FindLookAtRotation(PlayerCamera->GetComponentLocation(), LookAtVector)};
	PlayerController->SetControlRotation(CameraRotation);
}

void AERKeypadBase::UpdateSelectedButton()
{
#pragma region Nullchecks
	if (!OutlineButtonMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|OutlineButtonMat is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	if (!Button2DArray.IsValidIndex(Button2DArrayY))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Button2DArrayY is not valid index"), *FString(__FUNCTION__))
		return;
	}
	if (!Button2DArray[Button2DArrayY].ButtonArray.IsValidIndex(Button2DArrayX))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Button2DArrayX is not valid index"), *FString(__FUNCTION__))
		return;
	}

	// Reset outline button if button is already selected
	if (SelectedButton.Mesh)
	{
		SelectedButton.Mesh->SetOverlayMaterial(nullptr);
	}

	SelectedButton = Button2DArray[Button2DArrayY].ButtonArray[Button2DArrayX];
	SelectedButton.Mesh->SetOverlayMaterial(OutlineButtonMat);
}

void AERKeypadBase::StartLedBlinking()
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
		if (OnEndLedBlinking.IsBound())
		{
			OnEndLedBlinking.Execute();
		}
	}
}
