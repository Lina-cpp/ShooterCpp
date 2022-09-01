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

	//Checking if character is dead - used in char animation
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;	//health bar

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//taking damage
	virtual float TakeDamage
	(
    	float DamageAmount,
    	struct FDamageEvent const & DamageEvent,
    	class AController * EventInstigator,
    	AActor * DamageCauser
	) override;

	//shooting
	void Shoot();

private:

	//movement functions #movement
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	//Gamepad rotation helper
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	//Health
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	float Health;


	//restrict bp to only classes that are subclasses of the gun.cpp class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	//the gun var.
	UPROPERTY()
	AGun* Gun;


};
