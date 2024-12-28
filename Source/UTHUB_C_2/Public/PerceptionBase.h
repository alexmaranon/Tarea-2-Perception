// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PerceptionBase.generated.h"

//"Template" for detecting methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTHUB_C_2_API UPerceptionBase : public USceneComponent
{
	GENERATED_BODY()

	friend class UPerceptionComponent;

public:	
	UPerceptionBase();

protected:
	virtual void BeginPlay() override;

	
	virtual void DetectActors(AActor* DetectingActor, float DetectArea,float TimeInBetween);
	virtual void StopDetecting(AActor* DetectingActor);

	UFUNCTION(BlueprintCallable, Category = "Perception")
	void ReceiveDetectActors(AActor* DetectingActor);

	UFUNCTION(BlueprintCallable, Category = "Perception")
	void ReceiveStopDetecting(AActor* DetectingActor);



	
		
};
