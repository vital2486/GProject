// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GPROJECT_API APCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WEnemyHealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* EnemyHealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WInteractionToTransferVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* InteractionToTransferVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WSnowyTotemNotice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* SnowyTotemNotice;

	bool bEnemyHealthBarVisible;
	bool bInteractionToTransferVolumeVisible;
	bool bSnowyTotemNoticeVisible;

	void DisplayEnemyHealthBar();
	void RemoveEnemyHealthBar();
	
	void DisplayInteractionToTransferVolume();
	void RemoveInteractionToTransferVolume();

	void DisplaySnowyTotemNotice();
	void RemoveSnowyTotemNotice();

	FVector EnemyLocation;
	FVector TransferVolumeLocation;
	FVector SnowyTotemNoticeLocation;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
