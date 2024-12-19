// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "FloatingWordSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class XRDC_API UFloatingWordSubsystem : public USubsystem
{
	GENERATED_BODY()
	
	void Initialize(FSubsystemCollectionBase& Collection) override;
};
