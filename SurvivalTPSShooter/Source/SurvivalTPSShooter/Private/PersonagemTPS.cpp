// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonagemTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APersonagemTPS::APersonagemTPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SprintArmCamera"));
	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(FName("CameraPlayer"));
	PlayerCamera->SetupAttachment(SpringArmCamera);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APersonagemTPS::BeginPlay()
{
	Super::BeginPlay();
	
}

void APersonagemTPS::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void APersonagemTPS::MoveRigth(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

// Called every frame
void APersonagemTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonagemTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APersonagemTPS::MoveForward);
	PlayerInputComponent->BindAxis("MoveRigth", this, &APersonagemTPS::MoveRigth);

	//Move to Axis Y
	PlayerInputComponent->BindAxis("LookUpAndDow", this, &APersonagemTPS::AddControllerPitchInput);
	//Move to Axis X
	PlayerInputComponent->BindAxis("LookRigthAndLeft", this, &APersonagemTPS::AddControllerYawInput);

}

