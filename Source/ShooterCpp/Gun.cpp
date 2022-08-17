// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating root and setting it as root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
		SetRootComponent(Root);
	//creating mesh comp. and attaching it to root
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
		Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	//creating emitter in rifle socket
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	//hold of player controller to get controller and set camera
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
		OwnerController->GetPlayerViewPoint(Location, Rotation);


	//Calculating LineTraceingByChannel
	FVector End = Location + Rotation.Vector() * MaxRange;
	//TODO LineTrace
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
	if(bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector(); //getting shot direction
		//spawning emmiter at place where we shot
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

		AActor *HitActor = Hit.GetActor(); //get hold of the actor
		if(HitActor != nullptr)
		{
			//Dealing Damage
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); //damage event
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);   //take damage
		}

	}
 
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

