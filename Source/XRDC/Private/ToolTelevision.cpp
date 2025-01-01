// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolTelevision.h"
#include "Components/BoxComponent.h"
#include "FloatingWordManager.h"
#include <Kismet/GameplayStatics.h>
#include "Materials/MaterialInterface.h"
#include "FloatingWord.h"

AToolTelevision::AToolTelevision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PowerButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Power Button"));
	PowerButtonCollision->SetupAttachment(RootComponent);

	NextButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Next Button"));
	NextButtonCollision->SetupAttachment(RootComponent);

	ConfirmButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Confirm Button"));
	ConfirmButtonCollision->SetupAttachment(RootComponent);

	InteractionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Area"));
	InteractionArea->SetupAttachment(RootComponent);
}

void AToolTelevision::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFloatingWordManager::StaticClass(), FoundActors);
	GameManager = Cast<AFloatingWordManager>(FoundActors[0]);

	check(ToolList.Num() == ToolScreenMaterialList.Num());
	ScreenPlane->SetMaterial(0, BlackScreenMaterial);
}

void AToolTelevision::HitPowerButton()
{
	if(CurrToolInd == 255){
		CurrToolInd = (ToolIndBeforeShutDown == 255) ? 0 : ToolIndBeforeShutDown;
		ScreenPlane->SetMaterial(0, ToolScreenMaterialList[CurrToolInd]);
	}
	else {
		ToolIndBeforeShutDown = CurrToolInd;
		CurrToolInd = 255;
		ScreenPlane->SetMaterial(0, BlackScreenMaterial);
		GetWorldTimerManager().ClearTimer(SpawningTimerHandle);
	}
}

void AToolTelevision::HitNextButton()
{
	if (CurrToolInd == 255) return;
	CurrToolInd = (CurrToolInd == ToolList.Num() - 1) ? 0 : CurrToolInd + 1;
	if (CurrToolInd == PrevGrabbedToolInd) {
		ScreenPlane->SetMaterial(0, GrabbedScreenMaterial);
	}
	else {
		ScreenPlane->SetMaterial(0, ToolScreenMaterialList[CurrToolInd]);
	}
	
}

bool AToolTelevision::HitConfirmButton()
{
	if (CurrToolInd == 255) return false;
	if (PrevGrabbedToolInd != CurrToolInd) {
		PrevGrabbedToolInd = CurrToolInd;
		SpawnTool();
		GetWorld()->GetTimerManager().SetTimer(SpawningTimerHandle, this, &AToolTelevision::SpawnTool, SpawnTimerInterval, true);
		return true;
	}
	return false;
}

void AToolTelevision::ToolGrabbed()
{
	GetWorldTimerManager().ClearTimer(SpawningTimerHandle);
	if (CurrToolInd != 255) {
		ScreenPlane->SetMaterial(0, GrabbedScreenMaterial);
	}
}

void AToolTelevision::SpawnTool()
{
	FActorSpawnParameters SpawnInfo;
	AFloatingWord* i_spawnedWord = GetWorld()->SpawnActor<AFloatingWord>(ToolList[CurrToolInd],
		GetSpawningPosition(), FRotator(0, 0, 0), SpawnInfo);
	if (i_spawnedWord) {
		i_spawnedWord->SetDeviationDirection(GetDeviationVector());
		i_spawnedWord->SetStartPosition(GetSpawningPosition());
		i_spawnedWord->SetManager(GameManager);
	}
}


