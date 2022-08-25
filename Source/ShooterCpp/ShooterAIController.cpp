// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    if(AIBehavior != nullptr)
    {   
        //BehaviorTree
        RunBehaviorTree(AIBehavior);
        //get player pawn
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        //Blackboard
        GetBlackboardComponent()->SetValueAsVector( TEXT("PlayerLocation"), PlayerPawn->GetActorLocation() );
    }

/* 
    //get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(LineOfSightTo(PlayerPawn)) //if actor see PlayerPawn(us)
    {
        SetFocus(PlayerPawn);   //set focus at player
        MoveToActor(PlayerPawn, AcceptanceRadius); //Move towards us and stops X units before us
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay); //stop focusing on us
        StopMovement();  //stop following
    }
*/
}
