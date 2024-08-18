// Fill out your copyright notice in the Description page of Project Settings.

// Related Actors/Components
#include "ContentViewer.h"
#include "UMG_ContentViewer.h"
#include "CineCameraActor.h"
// Utilities
#include "Misc/Paths.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
// Multimedia
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "FileMediaSource.h"
// UI
#include "Components/WidgetComponent.h"
#include "Components/Image.h"
// Materials
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AContentViewer::AContentViewer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ViewerComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ViewerContentReflector"), true);
	// ViewerComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AContentViewer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AContentViewer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void AContentViewer::DynamicMaterialInstances_Initialization(UUMG_ContentViewer* WBPContentViewerRef, bool &bIsSucceed)
// {
// 	if (SegmentedMotion != nullptr && WBPContentViewerRef != nullptr)
// 	{
// 		SegmentedMotion_Dynamic = UMaterialInstanceDynamic::Create(SegmentedMotion, this);
// 		WBPContentViewerRef->GaugeTexture_SegmentedMotion->SetBrushFromMaterial(SegmentedMotion_Dynamic);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("AContentViewer::DynamicMaterialInstance_SegmentedMotion: No SegmentMotion parent found - returning."));
// 		return;
// 	}

// 	if (Segmented != nullptr && WBPContentViewerRef != nullptr)
// 	{
// 		Segmented_Dynamic = UMaterialInstanceDynamic::Create(Segmented, this);
// 		WBPContentViewerRef->GaugeTexture_Segmented->SetBrushFromMaterial(Segmented_Dynamic);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("AContentViewer::DynamicMaterialInstance_SegmentedMotion: No Segmented parent found - returning."));
// 		return;
// 	}

// 	if (OuterCircle != nullptr && WBPContentViewerRef != nullptr)
// 	{
// 		OuterCircle_Dynamic = UMaterialInstanceDynamic::Create(OuterCircle, this);
// 		WBPContentViewerRef->GaugeTexture_OuterCircle->SetBrushFromMaterial(OuterCircle_Dynamic);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("AContentViewer::DynamicMaterialInstance_SegmentedMotion: No Segmented parent found - returning."));
// 		return;
// 	}

// 	bIsSucceed = true;
// }

// void AContentViewer::SegmentedMotionCircleAnimation()
// {
// 	if (!SegmentedMotion_Dynamic)
// 	{
// 		// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: SegmentedMotion_Dynamic is nullptr - returning."));
// 		GetWorld()->GetTimerManager().ClearTimer(SegmentedMotionAnimationHandle);
// 		return;
// 	}

// 	GetWorld()->GetTimerManager().SetTimer(SegmentedMotionAnimationHandle,
// 	[this]()
// 	{ 
// 		if (SegmentedMotionPosition <= 1 && SegmentedCirclePosition >= -1)
// 		{
// 			SegmentedMotionPosition += 0.006f;
// 			SegmentedCirclePosition -= 0.003f;

// 			SegmentedMotion_Dynamic->SetScalarParameterValue("Motion_SegmentPosition", SegmentedMotionPosition);
// 			SegmentedMotion_Dynamic->SetScalarParameterValue("SegmentPosition", SegmentedCirclePosition);
// 			// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: SegmentedMotionAnimation started with SegmentedMotionPosition `%f`."), SegmentedMotionPosition);
// 		}
// 		else
// 		{
// 			SegmentedMotionPosition = 0.0f;
// 			SegmentedCirclePosition = 0.0f;
// 		}
// 	},
// 	0.01f, true);
// }

// void AContentViewer::SegmentedCirclePercentageAnimation()
// {
// 	if (!Segmented_Dynamic)
// 	{
// 		// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: Segmented_Dynamic is nullptr - returning."));
// 		GetWorld()->GetTimerManager().ClearTimer(SegmentedCirclePercentageHandle);
// 		return;
// 	}

// 	GetWorld()->GetTimerManager().SetTimer(SegmentedCirclePercentageHandle,
// 	[this]()
// 	{ 
// 		if (SegmentedPercentage <= 1)
// 		{
// 			SegmentedPercentage += 0.0006f;
// 			Segmented_Dynamic->SetScalarParameterValue("SegmentPercentage", SegmentedPercentage);
// 			// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: SegmentedMotionAnimation started with SegmentedMotionPosition `%f`."), SegmentedMotionPosition);
// 		}
// 		else
// 		{
//             GetWorld()->GetTimerManager().ClearTimer(SegmentedCirclePercentageHandle);
//             return;
// 		}
// 	},
// 	0.01f, true);
// }

// void AContentViewer::OuterCircleAnimation()
// {
// 	if (!OuterCircle_Dynamic)
// 	{
// 		GetWorld()->GetTimerManager().ClearTimer(OuterCircleAnimationHandle);
// 		return;
// 	}

// 	GetWorld()->GetTimerManager().SetTimer(OuterCircleAnimationHandle,
// 	[this]()
// 	{
// 		if (bIsIncreasing)
// 		{
// 			if (OuterCirclePosition <= 0.35)
// 			{
// 				OuterCirclePosition += 0.002f;
// 				OuterCircle_Dynamic->SetScalarParameterValue("Outer_SegmentPosition", OuterCirclePosition);
// 				// UE_LOG(LogTemp, Warning, TEXT("AContentViewer::OuterCircleAnimation: Incremented SegmentedMotionPosition `%f`."), OuterCirclePosition);
// 			}
// 			else
// 			{
// 				bIsIncreasing = false;
// 				// UE_LOG(LogTemp, Warning, TEXT("AContentViewer::OuterCircleAnimation: Boolean state id `&d`"), bIsIncreasing)
// 			}
// 		}
// 		else
// 		{
// 			// UE_LOG(LogTemp, Warning, TEXT("AContentViewer::OuterCircleAnimation: Boolean state id `%d`"), bIsIncreasing)
// 			if (OuterCirclePosition > 0.0f)
// 			{
// 				OuterCirclePosition -= 0.002f;
// 				OuterCircle_Dynamic->SetScalarParameterValue("Outer_SegmentPosition", OuterCirclePosition);
// 				// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: Decremented SegmentedMotionPosition `%f`."), OuterCirclePosition);
// 			}
// 			else
// 			{
// 				bIsIncreasing = true;
// 			}
// 		}
// 	},
// 	0.01f, true);
// }

void AContentViewer::SetParentForSelf()
{
    ParentActor = Cast<ACineCameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACineCameraActor::StaticClass()));
    if (ParentActor)
    {
		// UE_LOG(LogTemp, Log, TEXT("AContentViewer::SetParentToSelf: `%s`."), *ParentActor->GetName());
		this->AttachToActor(ParentActor, FAttachmentTransformRules::KeepRelativeTransform);
    }
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::SetParentToSelf: No CineCameraActor found - returning."));
		return;
	}
}

void AContentViewer::SetUpMediaPlayers()
{
	if(MediaPlayer1)
	{
		MediaPlayer1->OpenSource(MediaSource1);
		MediaPlayer1->Play();
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer1 is set."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer1 is nullptr - returnung."));
		return;
	}

	if (MediaPlayer2)
	{
		MediaPlayer2->OpenSource(MediaSource2);
		MediaPlayer2->Play();
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer2 is set."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer2 is nullptr - returnung."));
		return;
	}
}

void AContentViewer::ResetReferences()
{
	ParentActor = nullptr;
	// SegmentedMotion_Dynamic = nullptr;
	// Segmented_Dynamic = nullptr;
	// OuterCircle_Dynamic = nullptr;
}

void AContentViewer::DetachSelfFromParent()
{
    if (GetAttachParentActor() != nullptr)
    {
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    }
}
