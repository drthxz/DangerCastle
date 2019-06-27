//#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
//#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "Teleportation.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// include draw debug helpers header file


ATeleportation::ATeleportation()
{
	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ATeleportation::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATeleportation::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ATeleportation::BeginPlay()
{
	Super::BeginPlay();

}

void ATeleportation::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	//if the overlapping actor is the specific actor we identified in the editor

	ADemoCharacter* Player = Cast<ADemoCharacter>(OtherActor);

	if (OtherActor==Player)
	{
		//UGameplayStatics::OpenLevel(this, "Level_02");
		
	}
}

void ATeleportation::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	//if the overlapping actor is the specific actor we identified in the editor
	if (OtherActor && (OtherActor != this) )
	{
		//print("Overlap End");
		//printFString("%s has left the Trigger Volume", *OtherActor->GetName());
	}
}