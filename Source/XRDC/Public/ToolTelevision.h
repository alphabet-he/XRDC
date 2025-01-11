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
	UBoxComponent* NextButtonCollision;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ConfirmButtonCollision;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<AFloatingWord>> ToolList;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> ToolScreenMaterialList;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* GrabbedScreenMaterial;

	UPROPERTY(BlueprintReadOnly)
	uint8 CurrToolInd = -1;

	UPROPERTY(BlueprintReadOnly)
	uint8 PrevGrabbedToolInd = -1;

	UPROPERTY(BlueprintReadOnly)
	uint8 ToolIndBeforeShutDown = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void HitPowerButton() override;

	UFUNCTION(BlueprintCallable)
	void HitNextButton();

	UFUNCTION(BlueprintCallable)
	bool HitConfirmButton();

	UFUNCTION()
	void SpawnTool();

	UFUNCTION(BlueprintCallable)
	void AddTool(TSubclassOf<AFloatingWord> i_toolClass, UMaterialInterface* i_screenMaterial);

public:
	UFUNCTION(BlueprintCallable)
	void ToolGrabbed();
};
