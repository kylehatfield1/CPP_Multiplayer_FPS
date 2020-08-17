// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherWeapon.h"

void ALauncherWeapon::Fire()
{
	AActor* Owner = GetOwner();
	if (Owner == NULL)
	{
		return;
	}

	FVector Out_EyeLocation;
	FRotator Out_EyeRotation;
	Owner->GetActorEyesViewPoint(Out_EyeLocation, Out_EyeRotation);

	FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);


	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (ProjectileClass)
	{
		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, Out_EyeRotation,SpawnParams);
	}
}