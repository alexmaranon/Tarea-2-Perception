// Fill out your copyright notice in the Description page of Project Settings.


#include "PerceptionSubsystem.h"
#include "PerceptionComponent.h"
#include "PerceptionBase.h"
#include "Kismet/GameplayStatics.h"

void UPerceptionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			RegisterDetectingActor();
		});
	GetWorld()->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &ThisClass::RegisterDetectingEnabledActor));
	
	
}

void UPerceptionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UPerceptionSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

UPerceptionSubsystem* UPerceptionSubsystem::GetPerceptionSubsystem(const UObject* WorldContextObject)
{
	if(WorldContextObject)
	{
		return WorldContextObject->GetWorld()->GetSubsystem<UPerceptionSubsystem>();
	}
	return nullptr;
}

void UPerceptionSubsystem::DoDetection(AActor* DetectingActor, const TSubclassOf<UPerceptionBase>& DetectionForm, const FPerceptionInfo& StructInfo)
{
	if(UPerceptionComponent* Comp = GetCustomDetectingComponent(DetectingActor))
	{
		Comp->DetectActors(DetectionForm, StructInfo.DetectArea, StructInfo.DetectionTime);

	}
}

void UPerceptionSubsystem::StopDetecting(AActor* DetectingActor)
{
	if (UPerceptionComponent* Comp = GetCustomDetectingComponent(DetectingActor))
	{
		Comp->StopDetecting();
	}
}

void UPerceptionSubsystem::AddDetectingForm(AActor* DetectingActor, const TSubclassOf<UPerceptionBase>& DetectionForm)
{
	if(UPerceptionComponent* Comp = GetCustomDetectingComponent(DetectingActor))
	{
		Comp->AddDetectingForm(DetectionForm);
	}
}

void UPerceptionSubsystem::RemoveDetectingForm(AActor* DetectingActor,	const TSubclassOf<UPerceptionBase>& DetectionForm)
{
	if (UPerceptionComponent* Comp = GetCustomDetectingComponent(DetectingActor))
	{
		Comp->RemoveDetectingForm(DetectionForm);
	}
}

//AllExecuteDetection
void UPerceptionSubsystem::DoMultipleDetection(const TSubclassOf<UPerceptionBase>& MultipleDetection, const FPerceptionInfo& StructInfo)
{
	for(auto DetectingActor : AbleDetectingActors)
	{
		GetCustomDetectingComponent(DetectingActor)->DetectActors(MultipleDetection,StructInfo.DetectArea, StructInfo.DetectionTime);
	}
}

void UPerceptionSubsystem::StopAllDetections()
{
	for (auto DetectingActor : AbleDetectingActors)
	{
		GetCustomDetectingComponent(DetectingActor)->StopDetecting();
	}
}

UPerceptionComponent* UPerceptionSubsystem::GetCustomDetectingComponent(AActor* DetectingActor) const
{
	
	if(DetectingActor && AbleDetectingActors.Contains(DetectingActor))
	{
		
		return DetectingActor->FindComponentByClass<UPerceptionComponent>();
	}
	return nullptr;
}

void UPerceptionSubsystem::RegisterDetectingActor()
{
	TArray<AActor*> AllDetectingActors;
	

	if(UWorld* World=GetWorld())
	{



		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), AllDetectingActors);
		for (auto FoundDetectingActors : AllDetectingActors)
		{
			
			RegisterDetectingEnabledActor(FoundDetectingActors);
		}
	}
	
	
	
}

void UPerceptionSubsystem::RegisterDetectingEnabledActor(AActor* InActor)
{
	if(InActor&&InActor->FindComponentByClass<UPerceptionComponent>())
	{
		AbleDetectingActors.AddUnique(InActor);
	}
	


}



