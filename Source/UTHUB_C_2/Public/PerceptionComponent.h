// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerceptionSubsystem.h"
#include "Components/ActorComponent.h"
#include "PerceptionComponent.generated.h"

class UPerceptionBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTHUB_C_2_API UPerceptionComponent : public UActorComponent
{
	GENERATED_BODY()

	friend UPerceptionSubsystem;

public:	
	// Sets default values for this component's properties
	UPerceptionComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void DetectActors(const TSubclassOf<UPerceptionBase>& DetectionForm, float DetectArea,float TimeInBetween);

	void StopDetecting();

	void AddDetectingForm(const TSubclassOf<UPerceptionBase>& NewDetectingForm);

	void RemoveDetectingForm(const TSubclassOf<UPerceptionBase>& RemoveDetecting);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UPerceptionBase>> DetectingForms;
	TSubclassOf<UPerceptionBase> CurrentDetectingForm;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
		
};
