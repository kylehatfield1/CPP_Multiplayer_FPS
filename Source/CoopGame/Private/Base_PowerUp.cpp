// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_PowerUp.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABase_PowerUp::ABase_PowerUp()
{
	PowerUpInterval = 0.0f;
	TotalNumTicks = 0;

	bIsPowerUpActive = false;

	SetReplicates(true);
}


void ABase_PowerUp::OnRep_PowerUpActive()
{
	OnPowerUpStateChanged(bIsPowerUpActive);
}


void ABase_PowerUp::OnTickPowerUp()
{
	TicksProcessed++;
	OnPowerUpTicked();

	if (TicksProcessed >= TotalNumTicks)
	{
		OnExpired();

		bIsPowerUpActive = false;
		OnRep_PowerUpActive();

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);
	}
}

void ABase_PowerUp::ActivatePowerUp()
{
	OnActivated();
	bIsPowerUpActive = true;
	OnRep_PowerUpActive();

	if (PowerUpInterval > 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &ABase_PowerUp::OnTickPowerUp, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerUp();
	}
}

void ABase_PowerUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABase_PowerUp, bIsPowerUpActive);
}