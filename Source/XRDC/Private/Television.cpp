// Fill out your copyright notice in the Description page of Project Settings.


#include "Television.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATelevision::ATelevision(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	ScreenPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen Plane"));
	ScreenPlane->SetupAttachment(RootComponent);
	SpawningPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawning Position"));
	SpawningPosition->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATelevision::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ATelevision::GetSpawningPosition()
{
	return SpawningPosition->GetComponentLocation();
}

FVector ATelevision::GetDeviationVector()
{
	return SpawningPosition->GetForwardVector();
}


