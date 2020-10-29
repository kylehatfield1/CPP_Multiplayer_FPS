// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Horde_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API AHorde_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHorde_GameMode();

protected:
	FTimerHandle TimerHandle_BotSpawner;

	FTimerHandle TimerHandle_NextWaveStart;

	int32 WaveCount;

	int32 NumBotsToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	float TimeBetweenWaves;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void SpawnNewBot();

	void SpawnBotTimerElapsed();
	
	void StartWave();

	void EndWave();

	void PrepareForNextWave();

	void CheckWaveState();

	void CheckAnyPlayerAlive();

	void GameOver();

public:
	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
