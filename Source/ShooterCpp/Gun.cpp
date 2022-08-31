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
	//creating emitter flash and sound in rifle socket
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzlSound, Mesh, TEXT("MuzzleFlashSocket"));
	
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if(bSuccess)
	{		
		//spawning emmiter and sound at place where we shot
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		AActor *HitActor = Hit.GetActor(); //get hold of the actor
		if(HitActor != nullptr)
		{
			//Dealing Damage
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); //damage event
			AController *OwnerController = GetOwnerController();
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

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	//get oewner controller
	AController *OwnerController = GetOwnerController();
	if (OwnerController == nullptr) 
		return false; //if it's null return false

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation); //getting player Viewport
	ShotDirection = -Rotation.Vector(); //getting shot direction


	//End of LineTraceingByChannel
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params; //fixing AI to not shot himself
	Params.AddIgnoredActor(this); //ignoring gun
	Params.AddIgnoredActor(GetOwner()); //ignoring actor so you can't get shot by your own weapon xd
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	//hold of player controller to get controller and set camera
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) 
		return nullptr;

	return OwnerPawn->GetController();
	
}

