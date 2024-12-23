// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingWord.generated.h"

class UBoxComponent;
class AFloatingWordManager;
UCLASS()
class XRDC_API AFloatingWord : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingWord();
 
protected:
	// components
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* GrabComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* CollisionBox;

	//variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* WordMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* ObjectMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isTool = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UpperBoundary = 75.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector DeviationDirection;

	UPROPERTY(BlueprintReadWrite)
	FVector StartPosition;

	UPROPERTY(BlueprintReadWrite)
	bool isMerging = false;

	UPROPERTY(BlueprintReadOnly)
	AFloatingWordManager* GameManager;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetDeviationDirection(FVector i_direction) {
		DeviationDirection = i_direction;
	};

	FORCEINLINE void SetStartPosition(FVector i_position) {
		StartPosition = i_position;
	};

	FORCEINLINE void SetManager(AFloatingWordManager* i_manager) {
		GameManager = i_manager;
	};

	UFUNCTION(BlueprintCallable)
	void TryMerge(AFloatingWord* other);

};
