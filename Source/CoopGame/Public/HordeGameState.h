// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HordeGameState.generated.h"


UENUM(BlueprintType)
enum class EWaveState : uint8
{
	WaitingToStart, 
	WaveInProgress,
	WaitingToComplete,
	WaveComplete,
	GameOver,
};


UCLASS()
class COOPGAME_API AHordeGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WaveState, Category = "GameState")
	EWaveState WaveState;

	UFUNCTION()
	void OnRep_WaveState(EWaveState OldState);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
	void WaveStateChanged(EWaveState NewState, EWaveState OldState);

public:
	void SetWaveState(EWaveState NewState);
};
