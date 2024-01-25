// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacter.h"
#include "Engine/World.h"
#include "Weapon.h"
#include "Engine/EngineTypes.h"

// Sets default values
ABotCharacter::ABotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	WeaponEnemy = GetWorld()->SpawnActor<AWeapon>(BP_WeaponTypeRifle, FTransform(), Parameters);
	WeaponEnemy->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SocketOfWeapon"));
	
}

// Called every frame
void ABotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

