// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_PowerUp.generated.h"

UCLASS()
class COOPGAME_API ABase_PowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_PowerUp();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
	float PowerUpInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
	int32 TotalNumTicks;

	UPROPERTY(ReplicatedUsing = OnRep_PowerUpActive)
	bool bIsPowerUpActive;

	FTimerHandle TimerHandle_PowerUpTick;

	int32 TicksProcessed;

	UFUNCTION()
	void OnTickPowerUp();

	UFUNCTION()
	void OnRep_PowerUpActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnPowerUpStateChanged(bool bNewIsActive);

public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnPowerUpTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
	void OnExpired();

	void ActivatePowerUp();
};
