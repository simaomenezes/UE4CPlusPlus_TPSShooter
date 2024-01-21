// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MeshWeapon"));


	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshOfWeapon(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));
	if (MeshOfWeapon.Succeeded())
	{
		MeshWeapon->SetSkeletalMesh(MeshOfWeapon.Object);
	}

	RootComponent = MeshWeapon;
	ArrowWeapon = CreateDefaultSubobject<UArrowComponent>(FName("ArrowGunBarrel"));
	ArrowWeapon->SetupAttachment(MeshWeapon, FName("MuzzleFlashSocket"));
	
	// ArrowWeapon->AttachToComponent(MeshWeapon, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MuzzleFlashSocket"));
	
	ArrowWeapon->SetRelativeLocation(FVector(1.5f, 0.f, -1.2f));
	ArrowWeapon->SetRelativeScale3D(FVector(0.3f, 0.8f, 0.7f));


}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Shoot()
{
	ArrowWeapon = FindComponentByClass<UArrowComponent>();
	if (ArrowWeapon != nullptr)
	{
		/*
		* Seta da arma é um componente do ator logo achar sua localização
		* utilizamos GetComponentLocation.
		* Se fosse a Arma seria GetActorLocation() pois é a arma é o actor que
		* possui um arrow(setadaarma) como component
		*/
		FVector ArrowBegin = ArrowWeapon->GetComponentLocation();
		FVector ArrowDirection = ArrowWeapon->GetComponentRotation().Vector();
		FVector ArrowEnd = ArrowBegin + (ArrowDirection * 1000);

		/*
		* O raio de raycast vai pecorrer até o fim
		* e precisa colocar as informações de HIT(impacto) em algum estrutura. Esta estrutura é 
		* a FHitResult
		*/
		FHitResult HitInfo;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		Params.bTraceComplex = true;

		bool HitSome = GetWorld()->LineTraceSingleByChannel(HitInfo, ArrowBegin, ArrowEnd, ECollisionChannel::ECC_Visibility, Params);
		if (HitSome)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Some"));
		}
		DrawDebugLine(GetWorld(), ArrowBegin, ArrowEnd, FColor::Red, false, 5.0f, (uint8)0, 1.0f);

	}
}

