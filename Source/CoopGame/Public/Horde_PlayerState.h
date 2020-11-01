// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Horde_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API AHorde_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PalyerState")
	void AddScore(float ScoreDelta);
	
};
