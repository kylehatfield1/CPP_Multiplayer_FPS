// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class COOPGAME_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> CameraShakeEffect; 

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamge;

	void PlayFireEffects(FVector TraceEnd);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

};
