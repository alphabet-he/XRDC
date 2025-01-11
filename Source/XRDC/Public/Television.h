// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingWordManager.h"
#include "Television.generated.h"

class UBoxComponent;
class UArrowComponent;
UCLASS()
class XRDC_API ATelevision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelevision(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* SpawningPosition;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ScreenPlane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* PowerButtonCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* InteractionArea;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BlackScreenMaterial;

	UPROPERTY(EditAnywhere)
	float SpawnTimerInterval = 8.0f;

	AFloatingWordManager* GameManager;

	FTimerHandle SpawningTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HitPowerButton();

public:	
	FVector GetSpawningPosition();
	FVector GetDeviationVector();

};
