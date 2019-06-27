
// Fill out your copyright notice in the Description page of Project Settings.

#include "Trap.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SpawnEnemy.h"





ATrap::ATrap()
{
	OnActorBeginOverlap.AddDynamic(this, &ATrap::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATrap::OnOverlapEnd);

}

void ATrap::BeginPlay()
{
	Super::BeginPlay();


}

void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTime) {
		time +=  1 * DeltaTime;
	}
	if (time >= 5.0f) {
		bIsTrap = true;
		bIsTime = false;
	}
}


void ATrap::OnOverlapBegin(class AActor* OverlappedAtcor, class AActor* OtherActor)
{

	
	if (OtherActor && (OtherActor != this)) {

		Character = Cast<ADemoCharacter>(OtherActor);
		if (Character) {

			bIsTime = true;
			Character->IsTrap = true;
			
			
		}
		

	}


}

void ATrap::OnOverlapEnd(class AActor* OverlappedAtcor, class AActor* OtherActor)
{
}

bool ATrap::getIsTrap()
{
	return bIsTrap;
}

void ATrap::setbIsTrap(bool trap)
{
	bIsTrap = trap;
}




