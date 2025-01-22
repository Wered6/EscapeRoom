// Fill out your copyright notice in the Description page of Project Settings.


#include "ERKeypad.h"
#include "Camera/CameraComponent.h"
#include "EscapeRoom/Character/ERCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AERKeypad::AERKeypad()
{
	PrimaryActorTick.bCanEverTick = false;

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

	// Reset of meshes
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

void AERKeypad::InteractStart_Implementation(AActor* OtherInstigator)
{
	Super::InteractStart_Implementation(OtherInstigator);

	SetPlayerAndCameraLocationRotation(OtherInstigator);

	AERCharacter* Character{Cast<AERCharacter>(OtherInstigator)};

#pragma region Nullchecks
	if (!SelectedButtonMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SelectedButton is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!OutlineButtonMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|OutlineButtonMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|Character is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	Character->EnterKeypadInputMode();
	Character->SetInteractionCheck(false);

	SelectedButtonMesh->SetOverlayMaterial(OutlineButtonMaterial);
}

void AERKeypad::KeypadMove_Implementation(const FVector2D& MovementVector)
{
#pragma region Nullchecks
	if (!SelectedButtonMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SelectedButtonMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!OutlineButtonMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|OutlineButtonMaterial is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	ButtonArrayX += MovementVector.X;
	// Wrap limit between 0 - 2
	ButtonArrayX = ButtonArrayX < 0 ? 2 : ButtonArrayX > 2 ? 0 : ButtonArrayX;

	ButtonArrayY -= MovementVector.Y;
	// Wrap limit between 0 - 3
	ButtonArrayY = ButtonArrayY < 0 ? 3 : ButtonArrayY > 3 ? 0 : ButtonArrayY;

	// Reset overlay material in old selected button mesh and assign in new
	SelectedButtonMesh->SetOverlayMaterial(nullptr);
	if (ButtonMeshArray.IsValidIndex(ButtonArrayX))
	{
		if (ButtonMeshArray[ButtonArrayY].Meshes.IsValidIndex(ButtonArrayX))
		{
			SelectedButtonMesh = ButtonMeshArray[ButtonArrayY].Meshes[ButtonArrayX];
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ButtonMeshArray[%d].Meshes[%d] is not valid index"), ButtonArrayX, ButtonArrayY)
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ButtonMeshArray[%d] is not valid index"), ButtonArrayX)
	}

#pragma region Nullchecks
	if (!SelectedButtonMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|SelectedButtonMesh is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	SelectedButtonMesh->SetOverlayMaterial(OutlineButtonMaterial);
}

void AERKeypad::KeypadAcceptButtonPressed_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonPressed"))
}

void AERKeypad::KeypadAcceptButtonReleased_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("KeypadAcceptButtonReleased"))
}

void AERKeypad::KeypadExit_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("KeypadExit"))
}

void AERKeypad::BeginPlay()
{
	Super::BeginPlay();

	PopulateButtonMeshArray();

	SelectedButtonMesh = ButtonMeshArray[1].Meshes[1];
}

void AERKeypad::SetPlayerAndCameraLocationRotation(AActor* Player) const
{
	UCameraComponent* PlayerCamera{Cast<UCameraComponent>(Player->GetComponentByClass(UCameraComponent::StaticClass()))};
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
	PlayerLocationXY.Z = Player->GetActorLocation().Z;
	Player->SetActorLocation(PlayerLocationXY);

	// Set camera location Z of PlayerLocationScene Z
	FVector CameraLocationZ{PlayerCamera->GetComponentLocation()};
	CameraLocationZ.Z = PlayerLocationScene->GetComponentLocation().Z;
	PlayerCamera->SetWorldLocation(CameraLocationZ);

	// Set camera rotation so player will look at keypad
	const FRotator CameraRotation{UKismetMathLibrary::FindLookAtRotation(PlayerCamera->GetComponentLocation(), GetActorLocation())};
	PlayerController->SetControlRotation(CameraRotation);
}

void AERKeypad::PopulateButtonMeshArray()
{
	FMeshArray FirstRowButtonMeshes, SecondRowButtonMeshes, ThirdRowButtonMeshes, FourthRowButtonMeshes;

	FirstRowButtonMeshes.Meshes.Add(ButtonOneMesh);
	FirstRowButtonMeshes.Meshes.Add(ButtonTwoMesh);
	FirstRowButtonMeshes.Meshes.Add(ButtonThreeMesh);
	SecondRowButtonMeshes.Meshes.Add(ButtonFourMesh);
	SecondRowButtonMeshes.Meshes.Add(ButtonFiveMesh);
	SecondRowButtonMeshes.Meshes.Add(ButtonSixMesh);
	ThirdRowButtonMeshes.Meshes.Add(ButtonSevenMesh);
	ThirdRowButtonMeshes.Meshes.Add(ButtonEightMesh);
	ThirdRowButtonMeshes.Meshes.Add(ButtonNineMesh);
	FourthRowButtonMeshes.Meshes.Add(ButtonDelMesh);
	FourthRowButtonMeshes.Meshes.Add(ButtonZeroMesh);
	FourthRowButtonMeshes.Meshes.Add(ButtonOKMesh);
	ButtonMeshArray.Add(FirstRowButtonMeshes);
	ButtonMeshArray.Add(SecondRowButtonMeshes);
	ButtonMeshArray.Add(ThirdRowButtonMeshes);
	ButtonMeshArray.Add(FourthRowButtonMeshes);
}
