// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCppGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERCPP_API AKillEmAllGameMode : public AShooterCppGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn *PawnKilled) override;

public:
	UFUNCTION(BlueprintCallable)
	void EndGame(bool bIsPlayerWinner);

};