// Fill out your copyright notice in the Description page of Project Settings.

#include "PerceptionComponent.h"
#include "PerceptionBase.h"


// Sets default values for this component's properties
UPerceptionComponent::UPerceptionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
	
}
//We add a detecting method and we use it
void UPerceptionComponent::DetectActors(const TSubclassOf<UPerceptionBase>& DetectionForm, float DetectArea,float TimeInBetween)
{
	if(DetectingForms.Contains(DetectionForm))
	{
		CurrentDetectingForm = DetectionForm;
		CurrentDetectingForm->GetDefaultObject<UPerceptionBase>()->DetectActors(GetOwner(), DetectArea,TimeInBetween);
	}
}
//We remove the detecting method and we stop detecting
void UPerceptionComponent::StopDetecting()
{
	if(CurrentDetectingForm)
	{
		CurrentDetectingForm->GetDefaultObject<UPerceptionBase>()->StopDetecting(GetOwner());
		CurrentDetectingForm = nullptr;
	}
}

void UPerceptionComponent::AddDetectingForm(const TSubclassOf<UPerceptionBase>& NewDetectingForm)
{
	if(NewDetectingForm)
	{
		DetectingForms.AddUnique(NewDetectingForm);
	}
}

void UPerceptionComponent::RemoveDetectingForm(const TSubclassOf<UPerceptionBase>& RemoveDetecting)
{
	if(RemoveDetecting)
	{
		DetectingForms.Remove(RemoveDetecting);
	}
}


// Called every frame
void UPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

