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
     
    //get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(LineOfSightTo(PlayerPawn)) //if actor see PlayerPawn(us)
    {
        //Blackboard components
        GetBlackboardComponent()->SetValueAsVector( TEXT("PlayerLocation"), PlayerPawn->GetActorLocation() );
        GetBlackboardComponent()->SetValueAsVector( TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation() );

    }
    else
    {
            GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation")); //clearing PlayerLocation
    }

}
