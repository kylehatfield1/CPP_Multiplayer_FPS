// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TrackerBot.generated.h"

class UHealthComponent;

UCLASS()
class COOPGAME_API ATrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrackerBot();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementForce;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TargetDistanceTollerance;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bUseVelocityChange;

	FVector NextPoint;

	FVector GetNextPathPoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void HandleTakeDamage(UHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
