// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    Crosshair = CreateWidget(this, CrosshairClass); //create widget
    if (Crosshair != nullptr) //check if not null
    {
        Crosshair->AddToViewport(); //make it visible
    }
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Warning, TEXT("We have finished"));

    Crosshair->RemoveFromViewport(); //removing crosshair when game ends
    if(bIsWinner)
    {
        //create widget
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr) //check if not null (in case we didn't add class in CreateWidget())
        {
            WinScreen->AddToViewport(); //adding our widget to viewport
        }
    }
    else //if we lose game
    {
        //create widget
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr) //check if not null (in case we didn't add class in CreateWidget())
        {
            LoseScreen->AddToViewport(); //adding our widget to viewport
        }
    }
    //setting timer to restart game after death
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

}
