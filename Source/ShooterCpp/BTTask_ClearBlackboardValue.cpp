// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
    NodeName = TEXT("Clear Blackboard Value"); 
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);    //do super when you override!
    // . because we are not using the pointer
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); //Clear key - so AI will leave us

    return EBTNodeResult::Succeeded;
}
