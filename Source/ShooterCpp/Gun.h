// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERCPP_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	//shooting
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	//Creating particle system - muzzle
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	//muzzle sound
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzlSound;

	//Creating particle system - impact	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;
	//sound at location
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	//max range of LineTraceingByChannel
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 10;

	//LineOfSight trace function
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	//drawing the line function
	AController* GetOwnerController() const;

};
