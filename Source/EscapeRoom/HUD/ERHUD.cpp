// Fill out your copyright notice in the Description page of Project Settings.


#include "ERHUD.h"

void AERHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AERHUD::DrawHUD()
{
	Super::DrawHUD();

	// TODO show dot after laptop intro, and change color to red when can interact with something
	DrawDotCenter();
}

void AERHUD::DrawDotCenter()
{
	if (DotCenter)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter{ViewportSize.X / 2.f, ViewportSize.Y / 2.f};

		const float TextureWidth{static_cast<float>(DotCenter->GetSizeX())};
		const float TextureHeight{static_cast<float>(DotCenter->GetSizeY())};

		const FVector2D TextureDrawPoint{
			ViewportCenter.X - TextureWidth / 2.f,
			ViewportCenter.Y - TextureHeight / 2.f
		};

		DrawTexture(
			DotCenter,
			TextureDrawPoint.X,
			TextureDrawPoint.Y,
			TextureWidth, TextureHeight,
			0.f,
			0.f,
			1.f,
			1.f,
			FLinearColor::White
		);
	}
}
