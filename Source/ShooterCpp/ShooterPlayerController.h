// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERCPP_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ImplementableLoadScores"))
	void LoadScoresOnScreen();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ImplementableSaveGame"))
	void SaveGameOnScreen();

protected:
	virtual void BeginPlay() override;

private:
	//Hud
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	//GameRestart Variables
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	FTimerHandle RestartTimer;


};
