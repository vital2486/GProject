// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Animation/AnimInstance.h"
#include "PCharacterPlayerController.h"
#include "LevelTransferVolume.h"
#include "SnowyTotem.h"
#include "Weapon.h"
#include "Enemy.h"



APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseTurnRate = 55.0f;
	BaseLookUpRate = 55.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	MaxHealth = 100.f;
	Health = 100.f;
	MaxStamina = 150.f;
	Stamina = 150.f;

	RunningSpeed = 650.f;
	SprintingSpeed = 950.f;

	StaminaDrainRate = 25.f;
	MinSprintStamina = 50.f;

	InterpSpeed = 15.f;

	bShiftKeyPressed = false;
	bInteractionKeyPressed = false;
	bLMBDown = false;
	bInterpToEnemy = false;
	bHasCombatTarget = false;
	bMovingForward = false;
	bMovingRight = false;
	bActivateRedTotem = false;
	bActivateYellowTotem = false;
	bActivateGreenTotem = false;
	bActivateBlueTotem = false;

	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PCharacterPlayerController = Cast<APCharacterPlayerController>(GetController());

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	float DeltaStamina = StaminaDrainRate * DeltaTime;

	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if (bShiftKeyPressed)
		{
			if (Stamina - DeltaStamina <= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				if (MovementStatus == EMovementStatus::EMS_Sprinting)
				{
					Stamina -= DeltaStamina;
				}
			}
			else
			{
				if (MovementStatus == EMovementStatus::EMS_Sprinting)
				{
					Stamina -= DeltaStamina;
				}
			}
			if (bMovingForward || bMovingRight)
			{
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
			else
			{
				SetMovementStatus(EMovementStatus::EMS_Normal);
				if (Stamina + DeltaStamina >= MaxStamina)
				{
					Stamina = MaxStamina;
				}
				else
				{
					Stamina += DeltaStamina;
				}
			}
		}
		else
		{
			if (Stamina + DeltaStamina >= MaxStamina)
			{
				Stamina = MaxStamina;
			}
			else
			{
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		if (bShiftKeyPressed)
		{
			if (Stamina - DeltaStamina <= 0.f)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else
			{
				if (MovementStatus == EMovementStatus::EMS_Sprinting)
				{
					Stamina -= DeltaStamina;
				}
				if (bMovingForward || bMovingRight)
				{
					SetMovementStatus(EMovementStatus::EMS_Sprinting);
				}
				else
				{
					SetMovementStatus(EMovementStatus::EMS_Normal);
					if (Stamina + DeltaStamina >= MaxStamina)
					{
						Stamina = MaxStamina;
					}
					else
					{
						Stamina += DeltaStamina;
					}
				}
			}
		}
		else
		{
			if (Stamina + DeltaStamina >= MinSprintStamina)
			{
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaStamina;
			}
			else
			{
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_Exhausted:
		if (bShiftKeyPressed)
		{
			Stamina = 0.f;
		}
		else
		{
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		if (Stamina + DeltaStamina >= MinSprintStamina)
		{
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaStamina;
		}
		else
		{
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	default:
		;
	}

	if (bInterpToEnemy && CombatTarget)
	{
		FRotator LookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());
		FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);

		SetActorRotation(InterpRotation);
	}
	if (CombatTarget)
	{
		CombatTargetLocation = CombatTarget->GetActorLocation();
		if (PCharacterPlayerController)
		{
			PCharacterPlayerController->EnemyLocation = CombatTargetLocation;
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::ShiftKeyPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::ShiftKeyReleased);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerCharacter::InteractionKeyPressed);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &APlayerCharacter::InteractionKeyReleased);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &APlayerCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &APlayerCharacter::LMBUp);
} 

void APlayerCharacter::MoveForward(float AxisValue)
{
	bMovingForward = false;
	if ((Controller != nullptr) && (AxisValue != 0.0f) && (!bAttacking) && (MovementStatus != EMovementStatus::EMS_Dead))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);

		bMovingForward = true;
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	bMovingRight = false;
	if ((Controller != nullptr) && (AxisValue != 0.0f) && (!bAttacking) && (MovementStatus != EMovementStatus::EMS_Dead))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
		
		bMovingRight = false;
	}
}

void APlayerCharacter::Jump()
{
	if (MovementStatus != EMovementStatus::EMS_Dead)
	{
		Super::Jump();
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void APlayerCharacter::ShiftKeyPressed()
{
	bShiftKeyPressed = true;
}

void APlayerCharacter::ShiftKeyReleased()
{
	bShiftKeyPressed = false;
}

void APlayerCharacter::InteractionKeyPressed()
{
	bInteractionKeyPressed = true;

	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	if (TransferLevel)
	{
		ALevelTransferVolume* LevelTransferVolume = Cast<ALevelTransferVolume>(TransferLevel);
		if (LevelTransferVolume)
		{
			LevelTransferVolume->TransferToLevel(this);
		}
	}

	if (OverlappingTotem)
	{
		ASnowyTotem* SnowyTotem = Cast<ASnowyTotem>(OverlappingTotem);
		if (SnowyTotem)
		{
			if (SnowyTotem->bInRedTotem)
			{
				SnowyTotem->SwitchOnRedTotem(this);
			}
			if (SnowyTotem->bInYellowTotem)
			{
				SnowyTotem->SwitchOnYellowTotem(this);
			}
			if (SnowyTotem->bInGreenTotem)
			{
				SnowyTotem->SwitchOnGreenTotem(this);
			}
			if (SnowyTotem->bInBlueTotem)
			{
				SnowyTotem->SwitchOnBlueTotem(this);
			}
		}
	}
}

void APlayerCharacter::InteractionKeyReleased()
{
	bInteractionKeyPressed = false;
}

void APlayerCharacter::LMBDown()
{
	bLMBDown = true;

	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	if (ActiveOverlappingItem)
	{
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);
		if (Weapon)
		{
			Weapon->Equip(this);
			SetActiveOverlappingItem(nullptr);
		}
	}
	else if (EquippedWeapon)
	{
		Attack();
	}
}

void APlayerCharacter::LMBUp()
{
	bLMBDown = false;
}

void APlayerCharacter::Attack()
{
	if (!bAttacking && MovementStatus != EMovementStatus::EMS_Dead)
	{
		bAttacking = true;
		SetInterpToEnemy(true);

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage)
		{
			int32 Section = FMath::RandRange(0, 1);
			
			switch(Section)
			{
				case 0 : 
					AnimInstance->Montage_Play(CombatMontage, 2.2f);
					AnimInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
					break;
				case 1 : 
					AnimInstance->Montage_Play(CombatMontage, 1.8f);
					AnimInstance->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
					break;
				default : 
					break;
			}
		}
		if (EquippedWeapon->SwingSound)
		{
			UGameplayStatics::PlaySound2D(this, EquippedWeapon->SwingSound);
		}
	}
}

void APlayerCharacter::AttackEnd()
{
	bAttacking = false;
	SetInterpToEnemy(false);

	if (bLMBDown)
	{
		Attack(); // 공격 버튼을 지속적으로 누르고 있을 때 공격이 끝나자마자 다시 공격
	}
}

void APlayerCharacter::DecrementHealth(float Amount)
{
	if (Health - Amount <= 0.f)
	{
		Health -= Amount;
		Die();
	}
	else
	{
		Health -= Amount;
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		Health -= DamageAmount;
		Die();
		if (DamageCauser)
		{
			AEnemy* Enemy = Cast<AEnemy>(DamageCauser);
			if (Enemy)
			{
				Enemy->bHasValidTarget = false;
			}
		}
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}

void APlayerCharacter::Die()
{
	if (MovementStatus == EMovementStatus::EMS_Dead) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage)
	{
		AnimInstance->Montage_Play(CombatMontage, 1.f);
		AnimInstance->Montage_JumpToSection(FName("Death"));
	}
	SetMovementStatus(EMovementStatus::EMS_Dead);
}

void APlayerCharacter::DeathEnd()
{
	GetMesh()->bPauseAnims = true;
	GetMesh()->bNoSkeletonUpdate = true;
}


void APlayerCharacter::PlaySwingSound()
{
	if (EquippedWeapon->SwingSound)
	{
		UGameplayStatics::PlaySound2D(this, EquippedWeapon->SwingSound);
	}
}

void APlayerCharacter::SetEquippedWeapon(AWeapon* WeaponToSet)
{
	// 장착한 무기가 있을 때, 즉 무기가 교체될 때 이전 무기는 Destroy 된다.
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}
	EquippedWeapon = WeaponToSet;
}

void APlayerCharacter::SetInterpToEnemy(bool Interp)
{
	bInterpToEnemy = Interp;
}

FRotator APlayerCharacter::GetLookAtRotationYaw(FVector Target)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);
	
	return LookAtRotationYaw;
}

void APlayerCharacter::SetSnowyTotem(ASnowyTotem* Totem)
{ 
	OverlappingTotem = Totem;
}

void APlayerCharacter::SetActivateRedTotem(bool Activate)
{ 
	bActivateRedTotem = Activate;
}

void APlayerCharacter::SetActivateYellowTotem(bool Activate)
{ 
	bActivateYellowTotem = Activate;
}

void APlayerCharacter::SetActivateGreenTotem(bool Activate)
{
	bActivateGreenTotem = Activate;
}

void APlayerCharacter::SetActivateBlueTotem(bool Activate)
{
	bActivateBlueTotem = Activate;
}

bool APlayerCharacter::TotemPuzzleSuccess()
{
	if (bActivateRedTotem && !bActivateYellowTotem && !bActivateGreenTotem && bActivateBlueTotem)
	{
		return true;
	}
	else
	{
		return false;
	}
}