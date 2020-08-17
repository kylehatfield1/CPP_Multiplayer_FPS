// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rifle.h"
#include "LauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API ALauncherWeapon : public ARifle
{
	GENERATED_BODY()

protected:
	virtual void Fire() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "LauncherWeapon")
	TSubclassOf<AActor> ProjectileClass;
};
