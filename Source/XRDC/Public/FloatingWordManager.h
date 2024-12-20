// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingWordManager.generated.h"

class AFloatingWord;
class ATelevision;

USTRUCT(BlueprintType)
struct XRDC_API FTelevisionSpawnInfo 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	ATelevision* Television;
	UPROPERTY(EditAnywhere)
	float SpawnTimerInterval;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFloatingWord>> WordSpawnList;
	UPROPERTY(EditAnywhere)
	uint8 currSpawningInd = -1;
};

UCLASS()
class XRDC_API AFloatingWordManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingWordManager();

protected:
	UPROPERTY(EditAnywhere)
	TArray<FTelevisionSpawnInfo> SpawnInfoList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnWords(uint8 i_spawnInfoInd);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
