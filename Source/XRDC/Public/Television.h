// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Television.generated.h"

class UArrowComponent;
UCLASS()
class XRDC_API ATelevision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelevision();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* SpawningPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FVector GetSpawningPosition();
	FVector GetDeviationVector();

};
