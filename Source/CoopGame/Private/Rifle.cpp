// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";
}




// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARifle::Fire()
{
	AActor* Owner = GetOwner();
	if (Owner == NULL)
	{
		return;
	}
	FVector Out_EyeLocation;
	FRotator Out_EyeRotation;
	Owner->GetActorEyesViewPoint(Out_EyeLocation, Out_EyeRotation);

	FVector ShotDirection = Out_EyeRotation.Vector();
	FVector TraceEnd = Out_EyeLocation + (ShotDirection * 10000);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	// Particle "Target" parameter
	FVector TracerEndPoint = TraceEnd;

	FHitResult Out_Hit;
	bool bHitSomething = GetWorld()->LineTraceSingleByChannel(Out_Hit, Out_EyeLocation, TraceEnd, ECC_Visibility, QueryParams);
	if (bHitSomething)
	{
		AActor* ActorHit = Out_Hit.GetActor();
		UGameplayStatics::ApplyPointDamage(ActorHit, 20.0f, ShotDirection, Out_Hit, Owner->GetInstigatorController(), this, DamageType);
		
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Out_Hit.ImpactPoint, Out_Hit.ImpactNormal.Rotation());
		}

		TracerEndPoint = Out_Hit.ImpactPoint;
	}
	// DrawDebugLine(GetWorld(), Out_EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);

	PlayFireEffects(TracerEndPoint);
}

void ARifle::PlayFireEffects(FVector TraceEnd)
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	if (TracerEffect)
	{
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);

		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TracerTargetName, TraceEnd);
		}
	}
}

