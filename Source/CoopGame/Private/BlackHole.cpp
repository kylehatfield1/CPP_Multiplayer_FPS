// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Mesh;

	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerCollisonSphere"));
	InnerSphere->SetSphereRadius(10);
	InnerSphere->SetupAttachment(Mesh);

	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
	
	OutterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GravitySphere"));
	OutterSphere->SetSphereRadius(3000);
	OutterSphere->SetupAttachment(Mesh);

}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	//Uses OverlappingComponents as an out parameter
	OutterSphere->GetOverlappingComponents(OverlappingComponents);

	for (int32 i = 0; i < OverlappingComponents.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComponents[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float GravityRadius = OutterSphere->GetScaledSphereRadius();
			const float ForceStrength = -2000;

			PrimComp->AddRadialForce(GetActorLocation(), GravityRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

