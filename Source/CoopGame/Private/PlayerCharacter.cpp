// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = false;
	CameraComp->SetupAttachment(SpringArmComp);
	bIsZoomed = false;
	ZoomedFOV = 65.0f;

	
	

}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ZoomTimeline = NewObject<UTimelineComponent>();
	DefaultFOV = CameraComp->FieldOfView;
	FOnTimelineFloat InterpFunction;
	InterpFunction.BindUFunction(this, FName("TimelineFloatRetun"));
	ZoomTimeline->AddInterpFloat(ZoomCurve, InterpFunction);
}


void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		float ControllerYaw = Controller->GetControlRotation().Yaw;
		FRotator NewRotation = FRotator(0.0f, ControllerYaw, 0.0f);

		FVector ForwardVector = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		float ControllerYaw = GetControlRotation().Yaw;
		FRotator NewRotation = FRotator(0.0f, ControllerYaw, 0.0f);

		FVector RightVector = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightVector, Value);
	}
}

void APlayerCharacter::BeginCrouch()
{
	Crouch();
}

void APlayerCharacter::EndCrouch()
{
	UnCrouch();
}

void APlayerCharacter::Zoom()
{
	if (ZoomCurve == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Zoom Curve Not set"));
		return;
	}

	if (bIsZoomed)
	{
		EndZoom();
	}
	else
	{
		ZoomTimeline->PlayFromStart();
		bIsZoomed = true;
	}
}

void APlayerCharacter::EndZoom()
{
	ZoomTimeline->ReverseFromEnd();
	bIsZoomed = false;
}

void APlayerCharacter::TimelineFloatRetun(float val)
{
	CameraComp->SetFieldOfView(val);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &APlayerCharacter::Zoom);
	//PlayerInputComponent->BindAction("Zoom", IE_DoubleClick, this, &APlayerCharacter::EndZoom);
}

FVector APlayerCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

