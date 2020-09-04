// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class UHealthComponent;
class URadialForceComponent;

UCLASS()
class COOPGAME_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UHealthComponent* HealthComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	float ExplosionImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	float ExplosiveForceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UMaterialInterface* ExplodedMaterial;

	UPROPERTY(ReplicatedUsing = "OnRep_Exploded")
	bool bAlreadyExploded;

	UFUNCTION()
	void OnRep_Exploded();

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComponent, float Health, float HealthDelta
		, const class UDamageType* DamageType, class AController* InstigatedBy
		, AActor* DamageCauser);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
