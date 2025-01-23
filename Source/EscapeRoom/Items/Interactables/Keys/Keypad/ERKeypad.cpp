// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypad.h"
#include "Camera/CameraComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AERKeypad::AERKeypad()
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

	// Rest of meshes
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
	LedGreenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LedGreenMesh"));
	LedGreenMesh->SetCollisionProfileName("NoCollision");
	LedGreenMesh->SetupAttachment(RootMesh);
	LedRedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LedRedMesh"));
	LedRedMesh->SetCollisionProfileName("NoCollision");
	LedRedMesh->SetupAttachment(RootMesh);

	// Player location scene from which player will look at Keypad after interacting with it
	PlayerLocationScene = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerLocationScene"));
	PlayerLocationScene->SetupAttachment(RootMesh);
	PlayerLocationScene->SetRelativeLocation(FVector(0.f, -150.f, 30.f));

	OutlineMeshComponentPtr = RootMesh;
}

void AERKeypad::BeginPlay()
{
	Super::BeginPlay();

	PopulateButton2DArray();
}

void AERKeypad::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	EnterKeypadMode();

	UpdateSelectedButton();
	// TODO add widget with controls
}

void AERKeypad::KeypadMove_Implementation(const FVector2D& MovementVector)
{
	if (!bCanNavigate)
	{
		return;
	}

	Button2DArrayX += MovementVector.X;
	// Wrap limit between 0 - 2
	Button2DArrayX = Button2DArrayX < 0 ? 2 : Button2DArrayX > 2 ? 0 : Button2DArrayX;

	Button2DArrayY -= MovementVector.Y;
	// Wrap limit between 0 - 3
	Button2DArrayY = Button2DArrayY < 0 ? 3 : Button2DArrayY > 3 ? 0 : Button2DArrayY;

	UpdateSelectedButton();
}

void AERKeypad::KeypadAcceptButtonPressed_Implementation()
{
	bCanNavigate = false;

	// All buttons except DEL and OK
	if (SelectedButton.Value < 10)
	{
		UserPassword = UserPassword + FString::FromInt(SelectedButton.Value);

		GreenLedFlash(LedShortFlashTime);
		// TODO add sound for green led
	}
	// DEL/OK
	else
	{
		// If DEL
		if (SelectedButton.Value == 10)
		{
			if (!UserPassword.IsEmpty())
			{
				UserPassword = UserPassword.LeftChop(1);
			}

			RedLedFlash(LedShortFlashTime);
			// TODO add sound for red led
		}
		// If OK
		else if (SelectedButton.Value == 20)
		{
			UE_LOG(LogTemp, Warning, TEXT("UserPassword: %s"), *UserPassword)

			StartCheckingPassword();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonPressed"))
	// TODO add sound for clicking
}

void AERKeypad::KeypadAcceptButtonReleased_Implementation()
{
	// If button is OK, do not allow to navigate, navigate will reset after blinking led ends
	bCanNavigate = SelectedButton.Value != 20;
	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonReleased"))
}

void AERKeypad::KeypadExit_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("KeypadExit"))
	EnterDefaultMode();
	Execute_DisplayInteractionUI(this, true);
}

void AERKeypad::PopulateButton2DArray()
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

void AERKeypad::EnterKeypadMode()
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

void AERKeypad::EnterDefaultMode() const
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!SelectedButton.Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SelectedButton.Mesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	// Turn off outline button
	SelectedButton.Mesh->SetOverlayMaterial(nullptr);

	AERCharacter* Character{Cast<AERCharacter>(InteractInstigator)};

#pragma region Nullchecks
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Character->ResetCameraTransform();
	// IMC_Default on IMC_Keypad off
	Character->EnterDefaultInputMode();
	// No perform interaction check in Character so InteractableActor is set as Keypad
	Character->SetCanCheckInteraction(true);
	Character->SetIndicatorVisibility(true);
}

void AERKeypad::LookAtKeypad() const
{
#pragma region Nullchecks
	if (!InteractInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|InteractInstigator is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	const UCameraComponent* PlayerCamera{Cast<UCameraComponent>(InteractInstigator->GetComponentByClass(UCameraComponent::StaticClass()))};
	APlayerController* PlayerController{UGameplayStatics::GetPlayerController(this, 0)};

#pragma region Nullchecks
	if (!PlayerLocationScene)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PlayerLocationScene is nullptr"), *FString(__FUNCTION__))
		return;
	}
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

	// Set camera rotation so player will look at keypad
	const FVector LookAtVector{GetActorLocation()};
	const FRotator CameraRotation{UKismetMathLibrary::FindLookAtRotation(PlayerCamera->GetComponentLocation(), LookAtVector)};
	PlayerController->SetControlRotation(CameraRotation);
}

void AERKeypad::UpdateSelectedButton()
{
#pragma region Nullchecks
	if (!OutlineButtonMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|OutlineButtonMaterial is nullptr"), *FString(__FUNCTION__))
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
	SelectedButton.Mesh->SetOverlayMaterial(OutlineButtonMaterial);
}

void AERKeypad::StartCheckingPassword()
{
	GetWorldTimerManager().SetTimer(LedBlinkTimerHandle, this, &AERKeypad::CheckingPassword, LedBlinkInterval, true, 0.f);
}

void AERKeypad::CheckingPassword()
{
	// Perform blink leds as many times as BlinkLoops counts
	if (LoopsCounter++ < BlinkLoops)
	{
		RedLedFlash(LedShortFlashTime);
		GreenLedFlash(LedShortFlashTime);
	}

	// End of blinking; BlinkLoops +1 to give one more loop without flashes
	if (LoopsCounter >= BlinkLoops + 1)
	{
		GetWorldTimerManager().ClearTimer(LedBlinkTimerHandle);
		LoopsCounter = 0;

		CheckPassword();
	}
}

void AERKeypad::CheckPassword()
{
	bCanNavigate = true;

	if (Password == UserPassword)
	{
		UnlockLockedItems();
		GreenLedFlash(LedLongFlashTime);
		EnterDefaultMode();
		DisableInteraction();
	}
	else
	{
		RedLedFlash(LedLongFlashTime);
		UserPassword.Empty();
		// TODO add sound
	}
}

void AERKeypad::GreenLedFlash(const float FlashTime)
{
	// Modify the material parameters at runtime
	UMaterialInstanceDynamic* DynamicMaterial{UMaterialInstanceDynamic::Create(LedMaterial, this)};

#pragma region Nullchecks
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LedGreenMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedGreenMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DynamicMaterial->SetScalarParameterValue(FName("Emissive"), 2.f);
	LedGreenMesh->SetMaterial(0, DynamicMaterial);

	// Set timer to flash led
	GetWorldTimerManager().SetTimer(GreenLedEmissiveTimerHandle, this, &AERKeypad::ResetGreenLedEmissive, FlashTime);
}

void AERKeypad::RedLedFlash(const float FlashTime)
{
	// Modify the material parameters at runtime
	UMaterialInstanceDynamic* DynamicMaterial{UMaterialInstanceDynamic::Create(LedMaterial, this)};

#pragma region Nullchecks
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|DynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LedGreenMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedGreenMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	DynamicMaterial->SetScalarParameterValue(FName("Emissive"), 2.f);
	LedRedMesh->SetMaterial(0, DynamicMaterial);

	// Set timer to flash led
	GetWorldTimerManager().SetTimer(RedLedEmissiveTimerHandle, this, &AERKeypad::ResetRedLedEmissive, FlashTime);
}

void AERKeypad::ResetGreenLedEmissive()
{
#pragma region Nullchecks
	if (!LedGreenMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedGreenMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ResetLedEmissive(LedGreenMesh);
}

void AERKeypad::ResetRedLedEmissive()
{
#pragma region Nullchecks
	if (!LedRedMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedRedMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ResetLedEmissive(LedRedMesh);
}

void AERKeypad::ResetLedEmissive(UStaticMeshComponent* LedMesh)
{
#pragma region Nullchecks
	if (!LedMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LedGreenMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedGreenMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!LedRedMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedRedMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	UMaterialInstanceDynamic* LedDynamicMaterial{UMaterialInstanceDynamic::Create(LedMaterial, this)};

#pragma region Nullchecks
	if (!LedDynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|LedDynamicMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	LedDynamicMaterial->SetScalarParameterValue(FName("Emissive"), 0.f);
	LedMesh->SetMaterial(0, LedDynamicMaterial);
}
