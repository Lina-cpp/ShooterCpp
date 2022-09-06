// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled); //super because of override!

    //UE_LOG(LogTemp, Warning, TEXT("Pawn was killed"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController()); //cast to get controller
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }
    
    // For loop over ShooterAI in World
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead()) //some AI is alive - return
        {
            return; //early return, because game can't be over yet
        }
    }

    EndGame(true); //AI dead - end game
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    //gives "a list" of all AController in World(aka level)
   for (AController* Controller : TActorRange<AController>(GetWorld()) ) //do a for loop over every Controller in the level
   {
    //true if player controller and bIsPlayerWinner || if not player controller and not bIsPlayerWinner
    //false if player controller and not bIsPlayerWinner || if not player controller and bIsPlayerWinner
      bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
      Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
      //Controller->GetPawn() so we won't lose controll at our pawn
      // if nullptr we still can move but camera goes crazy
   }
}