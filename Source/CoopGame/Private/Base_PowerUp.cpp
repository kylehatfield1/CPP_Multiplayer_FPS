// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_PowerUp.h"

// Sets default values
ABase_PowerUp::ABase_PowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerUpInterval = 0.0f;
	TotalNumTicks = 0;
}


// Called when the game starts or when spawned
void ABase_PowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABase_PowerUp::OnTickPowerUp()
{
	TicksProcessed++;
	OnPowerUpTicked();

	if (TicksProcessed >= TotalNumTicks)
	{
		OnExpired();

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);
	}
}

void ABase_PowerUp::ActivatePowerUp()
{
	if (PowerUpInterval > 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &ABase_PowerUp::OnTickPowerUp, PowerUpInterval, true, 0.0f);
	}
	else
	{
		OnTickPowerUp();
	}
}

