// Fill out your copyright notice in the Description page of Project Settings.

#include "Sphere_component.h"
#include "Arrow.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ASphere_component::ASphere_component()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);
	SphereComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TowerTrigger_1"));
	
	SphereComponent->SetupAttachment(Root);

	Cube_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Cube_Mesh->SetupAttachment(Root);


	OnActorBeginOverlap.AddDynamic(this, &ASphere_component::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ASphere_component::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphere_component::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Targetlocked) {
		UpdateTargetRotation();
	}
}


void ASphere_component::UpdateTargetRotation()
{
	ADemoCharacter* Characher = Cast<ADemoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Characher->GetActorLocation());


	Cube_Mesh->SetWorldRotation(NewRotation);
	
	
}

void ASphere_component::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	Characher = Cast<ADemoCharacter>(OtherActor);

	if (Characher)
	{
		
		Targetlocked = true;

	}

}


