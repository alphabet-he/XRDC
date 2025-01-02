// Fill out your copyright notice in the Description page of Project Settings.


#include "PotComponent.h"
#include "FloatingWord.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UPotComponent::UPotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPotComponent::BeginPlay()
{
	Super::BeginPlay();

	AFloatingWord* i_parent = Cast<AFloatingWord>(GetOwner());
	check(i_parent);

	PotMesh = i_parent->GetMesh();

	TraceQueueMaxLength = TraceDuration / UGameplayStatics::GetWorldDeltaSeconds(this);
}


// Called every frame
void UPotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTracing) {
		if (PotTrace.Num() == TraceQueueMaxLength) {
			PotTrace.RemoveAt(0);
			PotTrace.Add(PotMesh->GetComponentLocation());
		}
		else {
			PotTrace.Add(PotMesh->GetComponentLocation());
		}
	}


}

bool UPotComponent::CheckTraceIsCooking()
{
	TArray<FVector> PotTraceCopy(PotTrace);
	int i = -1;
	while (i < PotTraceCopy.Num()) {
		i++;
		int start = i;
		while ((i + 1 < PotTraceCopy.Num()) && (PotTraceCopy[i].Z <= PotTraceCopy[i + 1].Z + 5)) {
			i++;
		}
		int peak = i;
		while ((i + 1 < PotTraceCopy.Num()) && (PotTraceCopy[i].Z + 5 >= PotTraceCopy[i + 1].Z)) {
			i++;
		}
		int end = i;
		if (start < peak && peak < i) {
			float i_heightDiff = fmin(PotTraceCopy[peak].Z - PotTraceCopy[start].Z, PotTraceCopy[peak].Z - PotTraceCopy[end].Z);
			if (i_heightDiff < IsCookHeightThreshold) continue;
			float x_min = PotTraceCopy[start].X;
			float x_max = PotTraceCopy[start].X;
			float y_min = PotTraceCopy[start].Y;
			float y_max = PotTraceCopy[start].Y;
			for (int j = start; j < end; j++) {
				x_min = PotTraceCopy[j].X < x_min ? PotTraceCopy[j].X : x_min;
				x_max = PotTraceCopy[j].X > x_max ? PotTraceCopy[j].X : x_max;
				y_min = PotTraceCopy[j].Y < y_min ? PotTraceCopy[j].Y : y_min;
				y_max = PotTraceCopy[j].Y > y_max ? PotTraceCopy[j].Y : y_max;
			}
			float i_xyPlaneDist = sqrt(pow(x_max - x_min, 2) + pow(y_max - y_min, 2));
			if (i_xyPlaneDist > IsCookXYDistThreshold) continue;
			return true;
		}
	}
	return false;
}

void UPotComponent::StartTracing()
{
	PotTrace.Empty();
	bTracing = true;
}

void UPotComponent::StopTracing()
{
	bTracing = false;
}



