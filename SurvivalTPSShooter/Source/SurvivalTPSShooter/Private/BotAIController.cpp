// Fill out your copyright notice in the Description page of Project Settings.

#include "BotAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "BotCharacter.h"
#include "Engine/Engine.h"
#include "Weapon.h"

ABotAIController::ABotAIController()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensingComp"));

	PawnSensingComp->SensingInterval = .25f;
	PawnSensingComp->bOnlySensePlayers = true;
	PawnSensingComp->SetPeripheralVisionAngle(180.f);
	PawnSensingComp->SightRadius = 3000.f;

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));
}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotAIController::OnSeePawn);

	if (BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
		BlackboardComp->SetValueAsBool("Patrol", true);
	}
}

void ABotAIController::OnSeePawn(APawn* SensedPawn)
{
	if (BlackboardComp && SensedPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("I see you!"));

		BlackboardComp->SetValueAsObject("Enemy", SensedPawn);
		BlackboardComp->SetValueAsBool("Patrol", false);

		ABotCharacter* Bot = Cast<ABotCharacter>(GetPawn());
		Bot->WeaponEnemy->Shoot();
	}
}
