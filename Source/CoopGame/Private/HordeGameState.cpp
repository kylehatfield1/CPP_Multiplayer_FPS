// Fill out your copyright notice in the Description page of Project Settings.


#include "HordeGameState.h"
#include "Net/UnrealNetwork.h"

void AHordeGameState::OnRep_WaveState(EWaveState OldState)
{
	WaveStateChanged(WaveState, OldState);
}

void AHordeGameState::SetWaveState(EWaveState NewState)
{
	if (Role == ROLE_Authority)
	{
		EWaveState OldState = WaveState;
		WaveState = NewState;
		/// Explicitly call on server. On Rep is only automatic for clients.
		OnRep_WaveState(OldState);
	}
}

void AHordeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHordeGameState, WaveState);
}