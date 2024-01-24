// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALTPSSHOOTER_API ABotAIController : public AAIController
{
	GENERATED_BODY()

protected:
	ABotAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultOnly)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultOnly)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditDefaultOnly)
	class UBlackboardComponent* BlackboardComp;

	UFUNCTION()
	void OnSeePawn(class APawn* SensedPawn);

};
