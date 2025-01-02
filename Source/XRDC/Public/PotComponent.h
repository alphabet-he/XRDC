// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XRDC_API UPotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TraceDuration = 1.0f;

	UPROPERTY(EditAnywhere)
	float IsCookHeightThreshold = 40.0f;

	UPROPERTY(EditAnywhere)
	float IsCookXYDistThreshold = 75.0f;

	UPROPERTY()
	uint16 TraceQueueMaxLength = 60;

	UPROPERTY()
	bool bTracing = false;

	UPROPERTY()
	UStaticMeshComponent* PotMesh;

	UPROPERTY()
	TArray<FVector> PotTrace;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool CheckTraceIsCooking();

	UFUNCTION(BlueprintCallable)
	void StartTracing();

	UFUNCTION(BlueprintCallable)
	void StopTracing();

		
};
