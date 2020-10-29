// Fill out your copyright notice in the Description page of Project Settings.


#include "Horde_GameMode.h"
#include "HealthComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"


AHorde_GameMode::AHorde_GameMode()
{
	TimeBetweenWaves = 2.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}


void AHorde_GameMode::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}


void AHorde_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckWaveState();
	CheckAnyPlayerAlive();
}


void AHorde_GameMode::PrepareForNextWave()
{
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &AHorde_GameMode::StartWave, TimeBetweenWaves, false);
}


void AHorde_GameMode::StartWave()
{
	WaveCount++;

	NumBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &AHorde_GameMode::SpawnBotTimerElapsed, 1.0f, true, 0.0f);
}


void AHorde_GameMode::SpawnBotTimerElapsed()
{
	SpawnNewBot();

	NumBotsToSpawn--;

	if (NumBotsToSpawn <= 0)
	{
		EndWave();
	}
}


void AHorde_GameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);
}


void AHorde_GameMode::CheckWaveState()
{
	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if (NumBotsToSpawn > 0 || bIsPreparingForWave)
	{
		return;
	}

	bool bIsAnyBotAlive = false;

	for (FConstPawnIterator PawnIter = GetWorld()->GetPawnIterator(); PawnIter; PawnIter++)
	{
		APawn* TestPawn = PawnIter->Get();
		if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
		{
			continue;
		}
		UHealthComponent* HealthComp = Cast<UHealthComponent>(TestPawn->GetComponentByClass(UHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth() > 0.0f)
		{
			bIsAnyBotAlive = true;
			break;
		}
	}

	if (!bIsAnyBotAlive)
	{
		PrepareForNextWave();
	}
}


void AHorde_GameMode::CheckAnyPlayerAlive()
{
	for (FConstPlayerControllerIterator ControllerIter = GetWorld()->GetPlayerControllerIterator(); ControllerIter; ControllerIter++)
	{
		APlayerController* PlayerController = ControllerIter->Get();
		if (PlayerController && PlayerController->GetPawn())
		{
			APawn* PlayerPawn = PlayerController->GetPawn();
			UHealthComponent* HealthComp = Cast<UHealthComponent>(PlayerPawn->GetComponentByClass(UHealthComponent::StaticClass()));
			if (ensure(HealthComp) && HealthComp->GetHealth() > 0.0f)
			{
				//A Player Is Still Alive
				return;
			}
		}
	}

	//No Player Alive
	GameOver();
}


void AHorde_GameMode::GameOver()
{
	EndWave();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER! All Players are dead!"));
}
