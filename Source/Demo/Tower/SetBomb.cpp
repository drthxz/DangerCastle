// Fill out your copyright notice in the Description page of Project Settings.

#include "SetBomb.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "DemoCharacter.h"

// Sets default values
ASetBomb::ASetBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	MeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCmp"));
	MeshCmp->SetupAttachment(Root);
	MeshCmp->SetWorldScale3D(FVector(15.0f,15.0f,15.0f));
	MeshCmp->SetWorldLocation(FVector(0.0f, 7.0f, 1.0f));
	MeshCmp->SetWorldRotation(FRotator(0.0f, 0.0f, -90.0f));

	Fire_Piston = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire_Piston"));
	Fire_Piston->SetupAttachment(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(Root);

	FVector Scale = FVector(1.0f);
	BoxComponent->SetWorldScale3D(Scale * 1.5f);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASetBomb::OnOverlapBegin);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetWorldSize(30.0f);
	TextRender->SetHorizontalAlignment(EHTA_Center);
	TextRender->SetTextRenderColor(FColor::White);
	TextRender->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASetBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASetBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsfont) {
		MakeTextFacePlayer();

	}
}

void ASetBomb::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		bIsPut = true;

		bIsfont = true;

	}
}

void ASetBomb::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		bIsPut = false;
	}
}

void ASetBomb::MakeTextFacePlayer()
{
	ADemoCharacter* Characher = Cast<ADemoCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));


	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Characher->GetActorLocation());

	TextRender->SetWorldRotation(NewRotation);

}

