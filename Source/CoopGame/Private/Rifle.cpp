// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "CoopGame.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	BaseDamge = 20.0f;
	RateOfFire = 600.0f;

	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";

	SetReplicates(true);
}




// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
	TimeBetweenShots = 60 / RateOfFire;
}


void ARifle::Fire()
{
	if (Role < ROLE_Authority)
	{
		ServerFire();
		//return;
	}

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
	QueryParams.bReturnPhysicalMaterial = true;

	// Particle "Target" parameter
	FVector TracerEndPoint = TraceEnd;

	FHitResult Out_Hit;
	bool bHitSomething = GetWorld()->LineTraceSingleByChannel(Out_Hit, Out_EyeLocation, TraceEnd, COLLISION_WEAPON, QueryParams);
	if (bHitSomething)
	{
		float DamageToApply = BaseDamge;
		EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Out_Hit.PhysMaterial.Get());
		UParticleSystem* SelectedEffect = nullptr;

		switch (SurfaceType)
		{
		case SURFACE_FLESHDEFAULT:
			SelectedEffect = FleshImpactEffect;
			break;
		case SURFACE_FLESHVULNERABLE:
			SelectedEffect = FleshImpactEffect;
			DamageToApply *= 4.0f;
			break;
		default:
			SelectedEffect = DefaultImpactEffect;
			break;
		}

		AActor* ActorHit = Out_Hit.GetActor();
		UGameplayStatics::ApplyPointDamage(ActorHit, DamageToApply, ShotDirection, Out_Hit, Owner->GetInstigatorController(), this, DamageType);
		
		if (SelectedEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, Out_Hit.ImpactPoint, Out_Hit.ImpactNormal.Rotation());
		}

		TracerEndPoint = Out_Hit.ImpactPoint;
	}
	// DrawDebugLine(GetWorld(), Out_EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);

	PlayFireEffects(TracerEndPoint);

	LastFireTime = GetWorld()->TimeSeconds;
}


void ARifle::ServerFire_Implementation()
{
	Fire();
}


bool ARifle::ServerFire_Validate()
{
	return true;
}


void ARifle::StartFire()
{
	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &ARifle::Fire, TimeBetweenShots, true, FirstDelay);
}


void ARifle::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
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

	APawn* Owner = Cast<APawn>(GetOwner());
	if (Owner)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Owner->GetController());
		if (PlayerController)
		{
			PlayerController->ClientPlayCameraShake(CameraShakeEffect);
		}
	}
}

