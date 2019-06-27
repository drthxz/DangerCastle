// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DemoCharacter.h"



// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	MeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCmp"));
	MeshCmp->SetupAttachment(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(Root);

	FVector Scale = FVector(1.0f);
	BoxComponent->SetWorldScale3D(Scale * 1.5f);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlapBegin);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetWorldSize(30.0f);
	TextRender->SetHorizontalAlignment(EHTA_Center);
	TextRender->SetTextRenderColor(FColor::White);
	TextRender->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	//TextRender->SetText(TEXT("GO"));
	
}

void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsfont) {
		MakeTextFacePlayer();

	}
	
}


void ABomb::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		bIsTake = true;

		bIsfont = true;
	}
	
}

void ABomb::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		bIsTake = false;
	}
	
}

void ABomb::MakeTextFacePlayer()
{
	ADemoCharacter* Characher = Cast<ADemoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));


	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Characher->GetActorLocation());

	TextRender->SetWorldRotation(NewRotation);
}

