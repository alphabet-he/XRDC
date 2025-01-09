// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Television.h"
#include "ToolTelevision.generated.h"

class UBoxComponent;
class AFloatingWordManager;
class UMaterialInterface;
class AFloatingWord;
UCLASS()
class XRDC_API AToolTelevision : public ATelevision
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AToolTelevision(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* PowerButtonCollision;

	UPROPERTY(EditAnywhere)
	UBoxComponent* NextButtonCollision;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ConfirmButtonCollision;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionArea;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<AFloatingWord>> ToolList;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> ToolScreenMaterialList;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* GrabbedScreenMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BlackScreenMaterial;

	UPROPERTY(EditAnywhere)
	float SpawnTimerInterval = 8.0f;

	UPROPERTY(BlueprintReadOnly)
	uint8 CurrToolInd = -1;

	UPROPERTY(BlueprintReadOnly)
	uint8 PrevGrabbedToolInd = -1;

	UPROPERTY(BlueprintReadOnly)
	uint8 ToolIndBeforeShutDown = -1;

	AFloatingWordManager* GameManager;

	FTimerHandle SpawningTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void HitPowerButton();

	UFUNCTION(BlueprintCallable)
	void HitNextButton();

	UFUNCTION(BlueprintCallable)
	bool HitConfirmButton();

	UFUNCTION()
	void SpawnTool();

public:
	UFUNCTION(BlueprintCallable)
	void ToolGrabbed();
};
