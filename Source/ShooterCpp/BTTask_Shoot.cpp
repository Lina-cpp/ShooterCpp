// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot"); 
}


EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);    //do super when you override!

    if (OwnerComp.GetAIOwner() == nullptr)   //get hold of a pawn - AI controller to pawn
    {
        return EBTNodeResult::Failed;
    }

    //cast to get shoot()
    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot();

    return EBTNodeResult::Succeeded;
}
