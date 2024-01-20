// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonagemTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


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

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCharacterMovement()->AirControl = 0.05f;
	GetCharacterMovement()->JumpZVelocity = 425.f;
	GetCharacterMovement()->GravityScale = 1.5f;

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

void APersonagemTPS::Jump()
{
	printf("pula");
	bIsJump = true;
}

void APersonagemTPS::JumpStop()
{
	printf("nao pula");
	bIsJump = false;
}

void APersonagemTPS::PlayerCrouch()
{
	Crouch();
}

void APersonagemTPS::PlayerUncrouch()
{
	UnCrouch();
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

	PlayerInputComponent->BindAction("PlayerCrouch", EInputEvent::IE_Pressed, this, &APersonagemTPS::PlayerCrouch);
	PlayerInputComponent->BindAction("PlayerCrouch", EInputEvent::IE_Released, this, &APersonagemTPS::PlayerUncrouch);

	PlayerInputComponent->BindAction("PlayerJump", EInputEvent::IE_Pressed, this, &APersonagemTPS::Jump);
	PlayerInputComponent->BindAction("PlayerJump", EInputEvent::IE_Released, this, &APersonagemTPS::JumpStop);

}

