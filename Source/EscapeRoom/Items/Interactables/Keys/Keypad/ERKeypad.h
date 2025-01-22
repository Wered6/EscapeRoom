// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERKeypadInteface.h"
#include "EscapeRoom/Items/Interactables/Keys/ERKeyItem.h"
#include "ERKeypad.generated.h"

USTRUCT(BlueprintType)
struct FMeshArray
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="ER|Mesh")
	TArray<TObjectPtr<UStaticMeshComponent>> Meshes;
};

class URectLightComponent;

UCLASS()
class ESCAPEROOM_API AERKeypad : public AERKeyItem, public IERKeypadInterface
{
	GENERATED_BODY()

public:
	AERKeypad();

	/**
	 * Overriding InteractStart function from ERInteractInterface (derived from ERInteractableActor in KeyItem)
	 */
	virtual void InteractStart_Implementation(AActor* OtherInstigator) override;

	/**
	 * Overriding KeypadMove function from ERKeypadInterface
	 */
	virtual void KeypadMove_Implementation(const FVector2D& MovementVector) override;
	/**
	 * Overriding KeypadAcceptButtonPressed function from ERKeypadInterface
	 */
	virtual void KeypadAcceptButtonPressed_Implementation() override;
	/**
	 * Overriding KeypadAcceptButtonReleased function from ERKeypadInterface
	 */
	virtual void KeypadAcceptButtonReleased_Implementation() override;
	/**
	 * Overriding KeypadExit function from ERKeypadInterface
	 */
	virtual void KeypadExit_Implementation() override;

protected:
	virtual void BeginPlay() override;

private:
	/**
	 * Adjust Player and it's Camera location and rotation so it looks at keypad.
	 */
	void SetPlayerAndCameraLocationRotation(AActor* Player) const;

	void PopulateButtonMeshArray();

	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonOneMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonTwoMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonThreeMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonFourMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonFiveMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonSixMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonSevenMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonEightMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonNineMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonDelMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonZeroMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonOKMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewL1Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewL2Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewR1Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ScrewR2Mesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> ShieldLogoMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> LedGreenMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Mesh")
	TObjectPtr<UStaticMeshComponent> LedRedMesh;

	UPROPERTY(EditDefaultsOnly, Category="ER|Utility")
	TObjectPtr<USceneComponent> PlayerLocationScene;

	// max x is 2
	// max y is 3
	// arrow up [x][y == 0 ? y = 3 : y -= 1]
	// arrow down [x][y == 3 ? y = 0 : y += 1]
	// arrow right [x == 0 ? x = 2 : x += 1]
	// arrow left [x == 2 ? x = 2 : x -= 1]
	UPROPERTY(VisibleAnywhere, Category="ER|Operation")
	int8 ButtonArrayX{1};
	UPROPERTY(VisibleAnywhere, Category="ER|Operation")
	int8 ButtonArrayY{1};
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="ER|Operation", meta=(AllowPrivateAccess="true"))
	TArray<FMeshArray> ButtonMeshArray;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="ER|Operation", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> SelectedButtonMesh;
	UPROPERTY(EditDefaultsOnly, Category="ER|Operation")
	TObjectPtr<UMaterialInterface> OutlineButtonMaterial;
	// TODO selected button when interacted with erkeypad should outline and we can switch it dynamically with inputs

#pragma region Input


#pragma endregion
};
