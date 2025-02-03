// Fill out your copyright notice in the Description page of Project Settings.


#include "ERTVScreenWidget.h"
#include "ERTVScreenSignWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"

void UERTVScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

#pragma region Nullchecks
	if (!TVScreenSignWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenSignWidgetClass is nullptr"), *FString(__FUNCTION__))
		return;
	}
	if (!PasswordHBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|PasswordHBox is nullptr"), *FString(__FUNCTION__))
		return;
	}
#pragma endregion

	for (int i = 0; i < Password.Len(); ++i)
	{
		UERTVScreenSignWidget* ScreenSignWidget{CreateWidget<UERTVScreenSignWidget>(this, TVScreenSignWidgetClass)};

		ScreenSignWidget->bBlinkFromStart = true;
		PasswordHBox->AddChildToHorizontalBox(ScreenSignWidget);
	}

	const TArray<UCanvasPanel*> TempArray{FirstPanel, SecondPanel, ThirdPanel, FourthPanel, FifthPanel, SixthPanel, SeventhPanel};
	HangmanPanelsArray = TempArray;

	UserPassword = FString::ChrN(Password.Len(), TEXT('_'));
}

bool UERTVScreenWidget::EnterSignToPassword(const FString& Sign)
{
#pragma region Nullchecks
	if (!EnteredSign)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s|EnteredSign is nullptr"), *FString(__FUNCTION__))
		return false;
	}
#pragma endregion

	EnteredSign->UpdateText(Sign.ToLower());

	bool bCorrectSign{false};
	const TCHAR SignChar{Sign.ToLower()[0]};

	for (int i = 0; i < Password.Len(); ++i)
	{
		if (SignChar == Password[i])
		{
			bCorrectSign = true;

			UERTVScreenSignWidget* TVScreenSignWidget{Cast<UERTVScreenSignWidget>(PasswordHBox->GetChildAt(i))};

#pragma region Nullchecks
			if (!TVScreenSignWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s|TVScreenSignWidget is nullptr"), *FString(__FUNCTION__))
				return false;
			}
#pragma endregion

			TVScreenSignWidget->StopBlinkAnimation();
			TVScreenSignWidget->UpdateText(Sign.ToLower());
			UserPassword[i] = SignChar;
		}
	}

	if (bCorrectSign)
	{
		return true;
	}
	if (HangmanPanelsArrayIndex < HangmanPanelsArray.Num())
	{
		HangmanPanelsArray[HangmanPanelsArrayIndex++]->SetVisibility(ESlateVisibility::Visible);
	}
	if (HangmanPanelsArrayIndex >= HangmanPanelsArray.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("you lost"))
		// TODO implement lost situation
	}
	return false;
}
