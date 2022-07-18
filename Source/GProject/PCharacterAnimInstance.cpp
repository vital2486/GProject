// Fill out your copyright notice in the Description page of Project Settings.


#include "PCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"

void UPCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			PlayerCharacter = Cast<APlayerCharacter>(Pawn);
		}
	}
}

void UPCharacterAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (PlayerCharacter == nullptr)
		{
			PlayerCharacter = Cast<APlayerCharacter>(Pawn);
		}
	}
}
