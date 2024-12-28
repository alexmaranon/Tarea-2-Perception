// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PerceptionSubsystem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPerceptionInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float DetectArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float DetectionTime;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDetected, AActor*, DetectedActor);

class UPerceptionComponent;
class UPerceptionBase;


UCLASS()
class UTHUB_C_2_API UPerceptionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

public:
	

	

	UFUNCTION(BlueprintPure)
	static UPerceptionSubsystem* GetPerceptionSubsystem(const UObject* WorldContextObject);

	

	UFUNCTION(BlueprintCallable)
	void DoDetection(AActor* DetectingActor, const TSubclassOf<UPerceptionBase>& DetectionForm, const FPerceptionInfo& StructInfo);

	UFUNCTION(BlueprintCallable)
	void StopDetecting(AActor* DetectingActor);

	UFUNCTION(BlueprintCallable)
	void AddDetectingForm(AActor* DetectingActor, const TSubclassOf<UPerceptionBase>& DetectionForm);

	UFUNCTION(BlueprintCallable)
	void RemoveDetectingForm(AActor* DetectingActor, const TSubclassOf<UPerceptionBase>& DetectionForm);

	UFUNCTION(BlueprintCallable)
	void DoMultipleDetection(const TSubclassOf<UPerceptionBase>& MultipleDetection, const FPerceptionInfo& StructInfo);

	UFUNCTION(BlueprintCallable)
	void StopAllDetections();

	TArray<AActor*> GetAbleDetectingActors() const { return  AbleDetectingActors; }

	UPROPERTY(BlueprintAssignable, Category = "Perception")
	FOnActorDetected OnActorDetected;

private:

	FPerceptionInfo DetectingStruct;

	UPerceptionComponent* GetCustomDetectingComponent(AActor* DetectingActor) const;

	void RegisterDetectingActor();
	void RegisterDetectingEnabledActor(AActor* InActor);


	UPROPERTY()
	TArray<AActor*> AbleDetectingActors;

};
