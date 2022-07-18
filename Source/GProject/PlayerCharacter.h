// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal		UMETA(DisplayName = "Normal"),
	EMS_Sprinting	UMETA(DisplayName = "Sprinting"),
	EMS_Dead		UMETA(DisplayName = "Dead"),

	EMS_MAX			UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal				UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum		UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted			UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering	UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX					UMETA(DisplayName = "Default Max")
};

UCLASS()
class GPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
		

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Running")
	float RunningSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Running")
	float SprintingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class APCharacterPlayerController* PCharacterPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AEnemy* CombatTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	class AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Items)
	class AItem* ActiveOverlappingItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	class ALevelTransferVolume* TransferLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	class ASnowyTotem* OverlappingTotem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class UAnimMontage* CombatMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Combat")
	FVector CombatTargetLocation;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasCombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	float InterpSpeed;

	bool bShiftKeyPressed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bInteractionKeyPressed;

	bool bLMBDown;

	bool bInterpToEnemy;
	
	bool bMovingForward;
	bool bMovingRight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
	bool bActivateRedTotem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
	bool bActivateYellowTotem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
	bool bActivateGreenTotem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
	bool bActivateBlueTotem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Jump() override;

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void TurnAtRate(float Rate);

	UFUNCTION()
	void LookUpAtRate(float Rate);

	UFUNCTION()
	void SetMovementStatus(EMovementStatus Status);

	UFUNCTION()
	void ShiftKeyPressed();

	UFUNCTION()
	void ShiftKeyReleased();

	UFUNCTION()
	void InteractionKeyPressed();

	UFUNCTION()
	void InteractionKeyReleased();

	UFUNCTION()
	void LMBDown();

	UFUNCTION()
	void LMBUp();

	UFUNCTION()
	void DecrementHealth(float Amount);

	UFUNCTION()
	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	UFUNCTION()
	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();

	UFUNCTION()
	bool TotemPuzzleSuccess();

	void SetEquippedWeapon(AWeapon* WeaponToSet);

	void SetInterpToEnemy(bool Interp);

	FRotator GetLookAtRotationYaw(FVector Target);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }

	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

	FORCEINLINE void SetTransferLevel(ALevelTransferVolume* Level) { TransferLevel = Level; }

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }

	void SetSnowyTotem(ASnowyTotem* Totem);

	void SetActivateRedTotem(bool Activate);
	void SetActivateYellowTotem(bool Activate);
	void SetActivateGreenTotem(bool Activate);
	void SetActivateBlueTotem(bool Activate);
	

};
