// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTimelineComponent;
class UHealthComponent;
class ARifle;

UCLASS()
class COOPGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ARifle> StartingWeapon;

	UPROPERTY(Replicated)
	ARifle* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UCurveFloat* ZoomCurve;

	//UPROPERTY(VisibleDefaultsOnly, Category = "Hide")
	UTimelineComponent* ZoomTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float ZoomedFOV;

	float DefaultFOV;

	bool bIsZoomed;

	bool bHasDied;

	UFUNCTION()
	void TimelineFloatRetun(float val);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	void StartFire();

	void StopFire();

	void Zoom();

	void EndZoom();

	void InitCamera();

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation()const override;
};