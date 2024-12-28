// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionBase.h"

// Sets default values for this component's properties
UPerceptionBase::UPerceptionBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPerceptionBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UPerceptionBase::DetectActors(AActor* DetectingActor, float DetectArea,float TimeInBetween)
{
	
	ReceiveDetectActors(DetectingActor);
}

void UPerceptionBase::StopDetecting(AActor* DetectingActor)
{
	ReceiveStopDetecting(DetectingActor);
}

void UPerceptionBase::ReceiveDetectActors(AActor* DetectingActor)
{
}


void UPerceptionBase::ReceiveStopDetecting(AActor* DetectingActor)
{
}


