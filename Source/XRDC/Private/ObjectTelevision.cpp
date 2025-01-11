// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectTelevision.h"
#include "FloatingWord.h"

void AObjectTelevision::HitPowerButton()
{
	if (CurrObjectInd == 255) {
		CurrObjectInd = 0;
		ScreenPlane->SetMaterial(0, TurnedOnScreenMaterial);
		SpawnObject();
		GetWorld()->GetTimerManager().SetTimer(SpawningTimerHandle, this, &AObjectTelevision::SpawnObject, SpawnTimerInterval, true);
	}
	else {
		CurrObjectInd = 255;
		ScreenPlane->SetMaterial(0, BlackScreenMaterial);
		GetWorldTimerManager().ClearTimer(SpawningTimerHandle);
	}
}

void AObjectTelevision::AddObject(TSubclassOf<AFloatingWord> i_object, UMaterialInterface* i_newScreenMaterial)
{
	ObjectList.Add(i_object);
	TurnedOnScreenMaterial = i_newScreenMaterial;
	ScreenPlane->SetMaterial(0, TurnedOnScreenMaterial);
}

void AObjectTelevision::SpawnObject()
{
	FActorSpawnParameters SpawnInfo;
	AFloatingWord* i_spawnedWord = GetWorld()->SpawnActor<AFloatingWord>(ObjectList[CurrObjectInd],
		GetSpawningPosition(), FRotator(0, 0, 0), SpawnInfo);
	if (i_spawnedWord) {
		i_spawnedWord->SetDeviationDirection(GetDeviationVector());
		i_spawnedWord->SetStartPosition(GetSpawningPosition());
		i_spawnedWord->SetManager(GameManager);
	}
	CurrObjectInd = (CurrObjectInd == ObjectList.Num() - 1) ? 0 : CurrObjectInd + 1;
}
