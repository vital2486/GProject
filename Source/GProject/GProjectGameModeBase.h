// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GProjectGameModeBase.generated.h"

UCLASS()
class GPROJECT_API AGProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public : 
	AGProjectGameModeBase();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category="UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected : 
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY()
		UUserWidget* CurrentWidget;

};
