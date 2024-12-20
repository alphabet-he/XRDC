// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingWord.h"
#include "Components/BoxComponent.h"

// Sets default values
AFloatingWord::AFloatingWord()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* _RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	GrabComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Grab Component"));
	GrabComponent->SetupAttachment(Mesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFloatingWord::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingWord::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloatingWord::TryMerge(AFloatingWord* other)
{
	isMerging = true;
	other->isMerging = true;
}

