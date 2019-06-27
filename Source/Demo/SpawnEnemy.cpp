// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnEnemy.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"

#include "AI/AI_Character.h"
#include "Trap.h"

#include "Engine.h"


// Sets default values
ASpawnEnemy::ASpawnEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = 0.0f;


}



// Called when the game starts or when spawned
void ASpawnEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ASpawnEnemy::Spawn()
{
	//UWorld* world = GetWorld();

	if (currentTime >= 0.5f) {
		currentTime = 0;

		FRotator rotator = GetActorRotation();
		FVector location = GetActorLocation();

		AAI_Character* ToSpawn = Cast<AAI_Character>(UAIBlueprintHelperLibrary::SpawnAIFromClass(this, ToSpawn_BP, NULL, location, rotator, true));

	}

		
}

// Called every frame
void ASpawnEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	currentTime = currentTime + 1 * DeltaTime;

	//Spawn();

	
}

//void ASpawnEnemy::OnOverlapBegin(AActor * OverlappedAtcor, AActor * OtherActor)
//{
//
//
//	if (OtherActor && (OtherActor != this)) {
//
//		Character = Cast<ADemoCharacter>(OtherActor);
//
//
//
//		if (Character) {
//
//			if (currentTime >= 3.0f) {
//				currentTime = 0;
//
//				FRotator rotator = GetActorRotation();
//				FVector location = GetActorLocation();
//
//				AAI_Bot_Character2* ToSpawn = Cast<AAI_Bot_Character2>(UAIBlueprintHelperLibrary::SpawnAIFromClass(this, ToSpawn_BP, NULL, location, rotator, true));
//
//			}
//			Spawn();
//			Destroy();
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
//		}
//		
//	}
//
//}

