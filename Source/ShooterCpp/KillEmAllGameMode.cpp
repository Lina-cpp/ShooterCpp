// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"


void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled); //super because of override!

    UE_LOG(LogTemp, Warning, TEXT("Pawn was killed"));
}
