// Fill out your copyright notice in the Description page of Project Settings.


#include "EmissionController.h"

#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values for this component's properties
UEmissionController::UEmissionController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEmissionController::BeginPlay()
{
	Super::BeginPlay();

	this->OwnerInit();
	// ...
	
}


// Called every frame
void UEmissionController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEmissionController::ApplyDynamicMaterial()
{
	if (!ParentMaterialInstance || !Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::ApplyDynamicMaterial: Material Instance or Owner is nullptr - returning."));
		return;
	}

	UStaticMeshComponent* OwnerMeshComponent = Owner->FindComponentByClass<UStaticMeshComponent>();
	if (!OwnerMeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::ApplyDynamicMaterial: Failed to get UStaticMeshComponent - returning."));
		return;
	}

	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(ParentMaterialInstance, OwnerMeshComponent);
	if(!DynamicMaterialInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::ApplyDynamicMaterial: Failed to create dynamic material instance - returning."));
		return;
	}

	OwnerMeshComponent->SetMaterial(0, DynamicMaterialInstance);
	DynamicMaterialInstance->GetScalarParameterValue(StaticEmissionParameterName, StaticEmissionIntensity);
}

void UEmissionController::ResetDynamicMaterial()
{
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::ResetDynamicMaterial: Owner is nullptr - returning."));
		return;
	}

	UStaticMeshComponent* OwnerMeshComponent = Owner->FindComponentByClass<UStaticMeshComponent>();
	if (!OwnerMeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::ResetDynamicMaterial: Failed to get UStaticMeshComponent - returning - returning."));
		return;
	}

	if (!ParentMaterialInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::ResetDynamicMaterial: ParentMaterialInstance is nullptr - returning."));
		return;
	}
	OwnerMeshComponent->SetMaterial(0, ParentMaterialInstance);
	StaticEmissionIntensity = 0;
	DynamicMaterialInstance = nullptr;
	GetWorld()->GetTimerManager().ClearTimer(StaticEmissionTimerHandle);
}

void UEmissionController::IncreaseStaticEmissionParam_Timer()
{
	GetWorld()->GetTimerManager().SetTimer(StaticEmissionTimerHandle, this, &UEmissionController::IncreaseStaticEmissionParam, 0.01f, true);
}

void UEmissionController::IncreaseStaticEmissionParam()
{
	if (!DynamicMaterialInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::IncreaseStaticEmissionParam: DynamictMaterialInstance is nullptr - returning."));
		GetWorld()->GetTimerManager().ClearTimer(StaticEmissionTimerHandle);
		return;
	}

	if (StaticEmissionIntensity < 10)
	{
		StaticEmissionIntensity = StaticEmissionIntensity + 0.014f; //steps
		DynamicMaterialInstance->SetScalarParameterValue(StaticEmissionParameterName, StaticEmissionIntensity);

		UE_LOG(LogTemp, Log, TEXT("UEmissionController::IncreaseStaticEmissionParam: `%f`."), StaticEmissionIntensity);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(StaticEmissionTimerHandle);
		return;
	}
}

void UEmissionController::OwnerInit()
{
	Owner = this->GetOwner();
	if (Owner)
	{
		OwnerName = Owner->GetName();
		this->ApplyDynamicMaterial();
	}
	else
	{
		OwnerName = "nullptr";
		UE_LOG(LogTemp, Warning, TEXT("UEmissionController::OwnerInit: Actor is nullptr - returning."));
	}
}