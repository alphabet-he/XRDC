// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Television.h"
#include "ObjectTelevision.generated.h"

/**
 * 
 */
UCLASS()
class XRDC_API AObjectTelevision : public ATelevision
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UMaterialInterface* TurnedOnScreenMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AFloatingWord>> ObjectList;

	UPROPERTY(BlueprintReadOnly)
	uint8 CurrObjectInd = -1;

	UFUNCTION(BlueprintCallable)
	void HitPowerButton() override;

	UFUNCTION(BlueprintCallable)
	void AddObject(TSubclassOf<AFloatingWord> i_object, UMaterialInterface* i_newScreenMaterial);

	UFUNCTION()
	void SpawnObject();
};
