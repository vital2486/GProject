// Fill out your copyright notice in the Description page of Project Settings.


#include "Wisp.h"

// Sets default values
AWisp::AWisp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingSpeed = 2.0f;

}

// Called when the game starts or when spawned
void AWisp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWisp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime * FloatingSpeed) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 60.0f;
	RunningTime += DeltaTime * FloatingSpeed;
	SetActorLocation(NewLocation);


}

