// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerceptionBase.h"
#include "SphereDetection.generated.h"

/**
 * 
 */



UCLASS()
class UTHUB_C_2_API USphereDetection : public UPerceptionBase
{
	GENERATED_BODY()
	

public:

	virtual void DetectActors(AActor* DetectingActor, float DetectArea, float TimeInBetween) override;

	virtual void StopDetecting(AActor* DetectingActor) override;

	void DetectInArea(AActor* DetectingActor, float DetectArea);

	UFUNCTION(BlueprintCallable, Category = "Perception")
	bool IsDetectingInArea(AActor* TargetActor,AActor* DetectingActor, float DetectArea);


private:

	TMap<AActor*, FTimerHandle>DetectingTimerHandle;
	

};
