// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowyTotem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PCharacterPlayerController.h"
#include "PlayerCharacter.h"

// Sets default values
ASnowyTotem::ASnowyTotem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(GetRootComponent());

    InteractionVolumeRed = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolumeRed"));
    InteractionVolumeRed->SetupAttachment(GetRootComponent());

    InteractionVolumeYellow = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolumeYellow"));
    InteractionVolumeYellow->SetupAttachment(GetRootComponent());

    InteractionVolumeGreen = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolumeGreen"));
    InteractionVolumeGreen->SetupAttachment(GetRootComponent());

    InteractionVolumeBlue = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolumeBlue"));
    InteractionVolumeBlue->SetupAttachment(GetRootComponent());

    RedTotem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedTotem"));
    RedTotem->SetupAttachment(GetRootComponent());

    YellowTotem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YellowTotem"));
    YellowTotem->SetupAttachment(GetRootComponent());

    GreenTotem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenTotem"));
    GreenTotem->SetupAttachment(GetRootComponent());

    BlueTotem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueTotem"));
    BlueTotem->SetupAttachment(GetRootComponent());

    bInRedTotem = false;
    bInYellowTotem = false;
    bInGreenTotem = false;
    bInBlueTotem = false;
}

// Called when the game starts or when spawned
void ASnowyTotem::BeginPlay()
{
	Super::BeginPlay();
	
    InteractionVolumeRed->OnComponentBeginOverlap.AddDynamic(this, &ASnowyTotem::RedVolumeOnOverlapBegin);
    InteractionVolumeRed->OnComponentEndOverlap.AddDynamic(this, &ASnowyTotem::RedVolumeOnOverlapEnd);

    InteractionVolumeYellow->OnComponentBeginOverlap.AddDynamic(this, &ASnowyTotem::YellowVolumeOnOverlapBegin);
    InteractionVolumeYellow->OnComponentEndOverlap.AddDynamic(this, &ASnowyTotem::YellowVolumeOnOverlapEnd);

    InteractionVolumeGreen->OnComponentBeginOverlap.AddDynamic(this, &ASnowyTotem::GreenVolumeOnOverlapBegin);
    InteractionVolumeGreen->OnComponentEndOverlap.AddDynamic(this, &ASnowyTotem::GreenVolumeOnOverlapEnd);

    InteractionVolumeBlue->OnComponentBeginOverlap.AddDynamic(this, &ASnowyTotem::BlueVolumeOnOverlapBegin);
    InteractionVolumeBlue->OnComponentEndOverlap.AddDynamic(this, &ASnowyTotem::BlueVolumeOnOverlapEnd);
}

// Called every frame
void ASnowyTotem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnowyTotem::RedVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    bInRedTotem = true;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(this);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->DisplaySnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::RedVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bInRedTotem = false;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(nullptr);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->RemoveSnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::YellowVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    bInYellowTotem = true;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(this);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->DisplaySnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::YellowVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bInYellowTotem = false;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(nullptr);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->RemoveSnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::GreenVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    bInGreenTotem = true;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(this);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->DisplaySnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::GreenVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bInGreenTotem = false;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(nullptr);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->RemoveSnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::BlueVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    bInBlueTotem = true;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(this);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->DisplaySnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::BlueVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bInBlueTotem = false;

    if (OtherActor)
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->SetSnowyTotem(nullptr);
            if (PlayerCharacter->PCharacterPlayerController)
            {
                PlayerCharacter->PCharacterPlayerController->RemoveSnowyTotemNotice();
            }
        }
    }
}

void ASnowyTotem::SwitchOnRedTotem(APlayerCharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        if (PlayerCharacter->bActivateRedTotem)
        {
            PlayerCharacter->SetActivateRedTotem(false);
        }
        else
        {
            PlayerCharacter->SetActivateRedTotem(true);
        }
    }
}

void ASnowyTotem::SwitchOnYellowTotem(APlayerCharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        if (PlayerCharacter->bActivateYellowTotem)
        {
            PlayerCharacter->SetActivateYellowTotem(false);
        }
        else
        {
            PlayerCharacter->SetActivateYellowTotem(true);
        }
    }
}

void ASnowyTotem::SwitchOnGreenTotem(APlayerCharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        if (PlayerCharacter->bActivateGreenTotem)
        {
            PlayerCharacter->SetActivateGreenTotem(false);
        }
        else
        {
            PlayerCharacter->SetActivateGreenTotem(true);
        }
    }
}

void ASnowyTotem::SwitchOnBlueTotem(APlayerCharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        if (PlayerCharacter->bActivateBlueTotem)
        {
            PlayerCharacter->SetActivateBlueTotem(false);
        }
        else
        {
            PlayerCharacter->SetActivateBlueTotem(true);
        }
    }
}
