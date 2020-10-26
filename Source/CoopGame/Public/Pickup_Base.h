// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup_Base.generated.h"

class USphereComponent;
class UDecalComponent;
class ABase_PowerUp;

UCLASS()
class COOPGAME_API APickup_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup_Base();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	float CooldownDuration;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
	TSubclassOf<ABase_PowerUp> PowerUpClass;

	ABase_PowerUp* PowerUpInstance;

	FTimerHandle TimerHandle_RespawnTimer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Respawn();


public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
