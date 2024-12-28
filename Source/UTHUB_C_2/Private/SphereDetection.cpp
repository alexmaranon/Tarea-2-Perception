// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereDetection.h"
#include "PerceptionSubsystem.h"
#include "PerceptionComponent.h"
#include "Kismet/GameplayStatics.h"

void USphereDetection::DetectActors(AActor* DetectingActor, float DetectArea, float TimeInBetween)
{
	Super::DetectActors(DetectingActor, DetectArea,TimeInBetween);

	//We set a loop that executes the detecting in area method, Creating a new TimerHandle for each Detecting Actor so they dont share timer
	DetectingActor->GetWorld()->GetTimerManager().SetTimer(DetectingTimerHandle.FindOrAdd(DetectingActor), [this,DetectingActor, DetectArea]
	{
			this->DetectInArea(DetectingActor, DetectArea);
	},TimeInBetween,true);

}

void USphereDetection::StopDetecting(AActor* DetectingActor)
{
	Super::StopDetecting(DetectingActor);

	//We stop the loop and delete the TimeHandler
	if(DetectingActor)
	{

		DetectingActor->GetWorld()->GetTimerManager().ClearTimer(*DetectingTimerHandle.Find(DetectingActor));
		DetectingTimerHandle.Remove(DetectingActor);
	}
	
}

void USphereDetection::DetectInArea(AActor* DetectingActor, float DetectArea)
{

	
	UPerceptionSubsystem* PerceptionSubsystem = UPerceptionSubsystem::GetPerceptionSubsystem(DetectingActor->GetWorld());
	//We get the detecting actors that the SubSystem created when initialized so we dont have to iterate on all the actors again
	TArray<AActor*> DetectingActors = PerceptionSubsystem->GetAbleDetectingActors();


	//We draw the detecting sphere
	DrawDebugSphere(
		DetectingActor->GetWorld(),
		DetectingActor->GetActorLocation(),  // Start Position
		DetectArea,                          // Sphere Radius
		12,                                  // Número de segmentos (más alto = más suave)
		FColor::Red,                         // Color
		false,                               // No persistent lines
		0.5f                                 // Duration
	);

	UE_LOG(LogTemp, Warning, TEXT("DetectArea: %f"), DetectArea);
	for (AActor* Targetactor : DetectingActors)
	{

		if (DetectingActor == Targetactor)continue;
		//Check if its in the area range
		if (IsDetectingInArea(Targetactor, DetectingActor, DetectArea))
		{
			//We use the PerceptionSubsystem delegate to notify of the detected actors
			PerceptionSubsystem->OnActorDetected.Broadcast(Targetactor);

		}

	}
}


bool USphereDetection::IsDetectingInArea(AActor* TargetActor, AActor* DetectingActor,float DetectArea)
{
	
	
	//Sphere detection method
	if (!DetectingActor) return false;

	FVector ActorLocation = DetectingActor->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	float distanceBetween = FVector::Dist(TargetLocation, ActorLocation);

	UE_LOG(LogTemp, Warning, TEXT("DetectArea: %f"), distanceBetween);

	return distanceBetween <= DetectArea;


}
