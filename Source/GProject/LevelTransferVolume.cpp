// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolume.h"
#include "PlayerCharacter.h"
#include "PCharacterPlayerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelTransferVolume::ALevelTransferVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevelTransferVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (PCharacterPlayerController)
	{
		PCharacterPlayerController->TransferVolumeLocation = GetActorLocation();
	}

}

// Called every frame
void ALevelTransferVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransferVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
	if (Character)
	{
		Character->SetTransferLevel(this);
		if (Character->PCharacterPlayerController)
		{
			Character->PCharacterPlayerController->DisplayInteractionToTransferVolume();
		}
		//UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
	}
}

void ALevelTransferVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
	if (Character)
	{
		Character->SetTransferLevel(nullptr);
		if (Character->PCharacterPlayerController)
		{
			Character->PCharacterPlayerController->RemoveInteractionToTransferVolume();
		}
	}
}

void ALevelTransferVolume::TransferToLevel(APlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
		PlayerCharacter->SetTransferLevel(nullptr);
	}
}