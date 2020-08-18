// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ARifle;

UCLASS()
class COOPGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ARifle> StartingWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Walk")
	UCurveFloat* ZoomCurve;

	UPROPERTY()
	class UTimelineComponent* ZoomTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;

	float DefaultFOV;

	bool bIsZoomed;

	ARifle* CurrentWeapon;

	UFUNCTION()
	void TimelineFloatRetun(float val);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	void Fire();

	void Zoom();

	void EndZoom();

	void InitCamera();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation()const override;
};