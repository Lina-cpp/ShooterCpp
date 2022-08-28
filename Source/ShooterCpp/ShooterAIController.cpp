// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {   
        RunBehaviorTree(AIBehavior);    //BehaviorTree
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);     //get player pawn
        GetBlackboardComponent()->SetValueAsVector( TEXT("StartLocation"), GetPawn()->GetActorLocation() );
    }

}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}
