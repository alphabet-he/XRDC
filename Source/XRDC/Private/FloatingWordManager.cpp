// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingWordManager.h"
#include "FloatingWord.h"
#include "Television.h"
#include <Kismet/GameplayStatics.h>
#include "Floor.h"

// Sets default values
AFloatingWordManager::AFloatingWordManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFloatingWordManager::BeginPlay()
{
	Super::BeginPlay();

	AActor* i_floor = UGameplayStatics::GetActorOfClass(GetWorld(), AFloor::StaticClass());
	FloorHeight = i_floor->GetActorLocation().Z;
	
	if (SpawnInfoList.Num() > 0) {
		for (int i = 0; i < SpawnInfoList.Num(); i++) {
			if (SpawnInfoList[i].WordSpawnList.Num() == 0) continue;

			FTimerDelegate i_timerDelegate;
			FTimerHandle i_timerHandle;

			SpawnWords(i);
			i_timerDelegate.BindUFunction(this, FName("SpawnWords"), i);
			GetWorld()->GetTimerManager().SetTimer(i_timerHandle, i_timerDelegate, SpawnInfoList[i].SpawnTimerInterval, true);
		}
	}


}

void AFloatingWordManager::SpawnWords(uint8 i_spawnInfoInd)
{
	SpawnInfoList[i_spawnInfoInd].currSpawningInd++;
	if (SpawnInfoList[i_spawnInfoInd].currSpawningInd == SpawnInfoList[i_spawnInfoInd].WordSpawnList.Num()) {
		SpawnInfoList[i_spawnInfoInd].currSpawningInd = 0;
	}
	FActorSpawnParameters SpawnInfo;
	AFloatingWord* i_spawnedWord = GetWorld()->SpawnActor<AFloatingWord>(SpawnInfoList[i_spawnInfoInd].WordSpawnList[SpawnInfoList[i_spawnInfoInd].currSpawningInd],
			SpawnInfoList[i_spawnInfoInd].Television->GetSpawningPosition(), FRotator(0, 0, 0), SpawnInfo);
	if (i_spawnedWord) {
		i_spawnedWord->SetDeviationDirection(SpawnInfoList[i_spawnInfoInd].Television->GetDeviationVector());
		i_spawnedWord->SetStartPosition(SpawnInfoList[i_spawnInfoInd].Television->GetSpawningPosition());
		i_spawnedWord->SetManager(this);
	}
}


