// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"


UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }
    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) //if in LineOfSight
    {
        //follow actor
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {   
        //if no - leave
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }

}
