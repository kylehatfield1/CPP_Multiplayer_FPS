// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TrackerBot.generated.h"

class UHealthComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class COOPGAME_API ATrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrackerBot();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementForce;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TargetDistanceTollerance;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bUseVelocityChange;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float SelfDestructRate;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ExplosionDamage;

	UPROPERTY(EditAnywhere, Category = "FX")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, Category = "FX")
	USoundCue* SelfDestructWarningSound;

	UPROPERTY(EditAnywhere, Category = "FX")
	USoundCue* ExplodeSound;

	bool bAlreadyExploded;

	bool bStartedSelfDestruction;

	UMaterialInstanceDynamic* MatInst;

	FVector NextPoint;

	FVector GetNextPathPoint();

	FTimerHandle TimerHandle_SelfDamage;

	void DamageSelf();
	
	void SelfDestruct();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void HandleTakeDamage(UHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
