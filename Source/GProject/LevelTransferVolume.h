// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolume.generated.h"

UCLASS()
class GPROJECT_API ALevelTransferVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVolume();

	UPROPERTY(EditAnywhere, meta = (AllowPrivate = "true"))
	FString TransferLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* TransferVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class APCharacterPlayerController* PCharacterPlayerController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TransferToLevel(class APlayerCharacter* PlayerCharacter);

};
