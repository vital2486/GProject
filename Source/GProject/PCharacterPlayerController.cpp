// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacterPlayerController.h"
#include "Blueprint/UserWidget.h"

void APCharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	if (WEnemyHealthBar)
	{
		EnemyHealthBar = CreateWidget<UUserWidget>(this, WEnemyHealthBar);
		if (EnemyHealthBar)
		{
			EnemyHealthBar->AddToViewport();
			EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
		}
		FVector2D Alignment(0.f, 0.f);
		EnemyHealthBar->SetAlignmentInViewport(Alignment);
	}

	if (WInteractionToTransferVolume)
	{
		InteractionToTransferVolume = CreateWidget<UUserWidget>(this, WInteractionToTransferVolume);
		if (InteractionToTransferVolume)
		{
			InteractionToTransferVolume->AddToViewport();
			InteractionToTransferVolume->SetVisibility(ESlateVisibility::Hidden);
		}
		FVector2D Alignment(0.f, 0.f);
		InteractionToTransferVolume->SetAlignmentInViewport(Alignment);
	}

	if (WSnowyTotemNotice)
	{
		SnowyTotemNotice = CreateWidget<UUserWidget>(this, WSnowyTotemNotice);
		if (SnowyTotemNotice)
		{
			SnowyTotemNotice->AddToViewport();
			SnowyTotemNotice->SetVisibility(ESlateVisibility::Hidden);
		}
		FVector2D Alignment(0.f, 0.f);
		SnowyTotemNotice->SetAlignmentInViewport(Alignment);
	}
}

void APCharacterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyHealthBar)
	{
		FVector2D PositionInViewport;
		ProjectWorldLocationToScreen(EnemyLocation, PositionInViewport);
		PositionInViewport.Y -= 85.f;

		FVector2D SizeInViewport(300.f, 25.f);

		EnemyHealthBar->SetPositionInViewport(PositionInViewport);
		EnemyHealthBar->SetDesiredSizeInViewport(SizeInViewport);
	}

	if (InteractionToTransferVolume)
	{
		FVector2D PositionInViewport;
		ProjectWorldLocationToScreen(TransferVolumeLocation, PositionInViewport);

		FVector2D SizeInViewport(200.f, 50.f);

		InteractionToTransferVolume->SetPositionInViewport(PositionInViewport);
		InteractionToTransferVolume->SetDesiredSizeInViewport(SizeInViewport);
	}

	if (SnowyTotemNotice)
	{
		FVector2D PositionInViewport;
		ProjectWorldLocationToScreen(SnowyTotemNoticeLocation, PositionInViewport);

		FVector2D SizeInViewport(200.f, 50.f);

		SnowyTotemNotice->SetPositionInViewport(PositionInViewport);
		SnowyTotemNotice->SetDesiredSizeInViewport(SizeInViewport);
	}
}

void APCharacterPlayerController::DisplayEnemyHealthBar()
{
	if (EnemyHealthBar)
	{
		bEnemyHealthBarVisible = true;
		EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
	}
}


void APCharacterPlayerController::RemoveEnemyHealthBar()
{
	if (EnemyHealthBar)
	{
		bEnemyHealthBarVisible = false;
		EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APCharacterPlayerController::DisplayInteractionToTransferVolume()
{
	if (InteractionToTransferVolume)
	{
		bInteractionToTransferVolumeVisible = true;
		InteractionToTransferVolume->SetVisibility(ESlateVisibility::Visible);
	}
}

void APCharacterPlayerController::RemoveInteractionToTransferVolume()
{
	if (InteractionToTransferVolume)
	{
		bInteractionToTransferVolumeVisible = false;
		InteractionToTransferVolume->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APCharacterPlayerController::DisplaySnowyTotemNotice()
{
	if (SnowyTotemNotice)
	{
		bSnowyTotemNoticeVisible = true;
		SnowyTotemNotice->SetVisibility(ESlateVisibility::Visible);
	}
}

void APCharacterPlayerController::RemoveSnowyTotemNotice()
{
	if (SnowyTotemNotice)
	{
		bSnowyTotemNoticeVisible = false;
		SnowyTotemNotice->SetVisibility(ESlateVisibility::Hidden);
	}
}