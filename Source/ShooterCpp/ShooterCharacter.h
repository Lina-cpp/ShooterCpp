// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

//forward declaration of AGun
class AGun;

UCLASS()
class SHOOTERCPP_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	//movement functions #movement
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	//Gamepad rotation helper
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	//shooting
	void Shoot();

	//restrict bp to only classes that are subclasses of the gun.cpp class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	//the gun var.
	UPROPERTY()
	AGun* Gun;


};
