// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnowyTotem.generated.h"

UCLASS()
class GPROJECT_API ASnowyTotem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnowyTotem();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InteractionVolume")
    class UStaticMeshComponent* StaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InteractionVolume")
    class UBoxComponent* InteractionVolumeRed;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InteractionVolume")
    UBoxComponent* InteractionVolumeYellow;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InteractionVolume")
    UBoxComponent* InteractionVolumeGreen;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InteractionVolume")
    UBoxComponent* InteractionVolumeBlue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
    UStaticMeshComponent* RedTotem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
    UStaticMeshComponent* YellowTotem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
    UStaticMeshComponent* GreenTotem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
    UStaticMeshComponent* BlueTotem;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
    bool bInRedTotem;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
    bool bInYellowTotem;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
    bool bInGreenTotem;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Switch")
    bool bInBlueTotem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void RedVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void RedVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void YellowVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void YellowVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void GreenVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void GreenVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void BlueVolumeOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void BlueVolumeOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void SwitchOnRedTotem(class APlayerCharacter* PlayerCharacter);

    UFUNCTION()
    void SwitchOnYellowTotem(APlayerCharacter* PlayerCharacter);

    UFUNCTION()
    void SwitchOnGreenTotem(APlayerCharacter* PlayerCharacter);

    UFUNCTION()
    void SwitchOnBlueTotem(APlayerCharacter* PlayerCharacter);


};
