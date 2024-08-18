// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_ContentViewer.h"
// UI Components
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
// Materials
#include "Materials/MaterialInstanceDynamic.h"
// Actors
#include "ContentViewer.h"
// Utilities
#include "Misc/Paths.h"

void UUMG_ContentViewer::NativeConstruct()
{
}

void UUMG_ContentViewer::NativePreConstruct()
{
}

void UUMG_ContentViewer::DynamicMaterialInstances_Initialization(const AContentViewer* BPContentViewerRef, bool &bIsSucceed)
{
	if (BPContentViewerRef != nullptr && BPContentViewerRef->SegmentedMotion != nullptr)
	{
		SegmentedMotion_Dynamic = UMaterialInstanceDynamic::Create(BPContentViewerRef->SegmentedMotion, this);
		GaugeTexture_SegmentedMotion->SetBrushFromMaterial(SegmentedMotion_Dynamic);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UUMG_ContentViewer::DynamicMaterialInstances_Initialization: No BPContentViewerRef or SegmentMotion parent found - returning."));
        bIsSucceed = false;
		return;
	}

	if (BPContentViewerRef != nullptr && BPContentViewerRef->Segmented != nullptr)
	{
		Segmented_Dynamic = UMaterialInstanceDynamic::Create(BPContentViewerRef->Segmented, this);
		GaugeTexture_Segmented->SetBrushFromMaterial(Segmented_Dynamic);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UUMG_ContentViewer::DynamicMaterialInstance_SegmentedMotion: No BPContentViewerRef or Segmented parent found - returning."));
        bIsSucceed = false;
		return;
	}

	if (BPContentViewerRef != nullptr && BPContentViewerRef->OuterCircle != nullptr)
	{
		OuterCircle_Dynamic = UMaterialInstanceDynamic::Create(BPContentViewerRef->OuterCircle, this);
		GaugeTexture_OuterCircle->SetBrushFromMaterial(OuterCircle_Dynamic);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UUMG_ContentViewer::DynamicMaterialInstance_SegmentedMotion: No BPContentViewerRef or Segmented parent found - returning."));
        bIsSucceed = false;
		return;
	}

    bIsSucceed = true;
}

void UUMG_ContentViewer::TimersInitialization()
{
    this->RE_OuterCircleAnimation();
    this->RE_SegmentedMotionCircleAnimation();
    this->SegmentedCirclePercentageAnimation();
}

void UUMG_ContentViewer::RE_SegmentedMotionCircleAnimation()
{
	if (!SegmentedMotion_Dynamic)
	{
		// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: SegmentedMotion_Dynamic is nullptr - returning."));
		GetWorld()->GetTimerManager().ClearTimer(SegmentedMotionAnimationHandle);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(SegmentedMotionAnimationHandle,
	[this]()
	{ 
		if (SegmentedMotionPosition <= 1 && SegmentedCirclePosition >= -1)
		{
			SegmentedMotionPosition += 0.006f;
			SegmentedCirclePosition -= 0.003f;

			SegmentedMotion_Dynamic->SetScalarParameterValue("Motion_SegmentPosition", SegmentedMotionPosition);
			SegmentedMotion_Dynamic->SetScalarParameterValue("SegmentPosition", SegmentedCirclePosition);
			// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: SegmentedMotionAnimation started with SegmentedMotionPosition `%f`."), SegmentedMotionPosition);
		}
		else
		{
			SegmentedMotionPosition = 0.0f;
			SegmentedCirclePosition = 0.0f;
		}
	},
	0.01f, true);
}

void UUMG_ContentViewer::SegmentedCirclePercentageAnimation()
{
	if (!Segmented_Dynamic)
	{
		// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: Segmented_Dynamic is nullptr - returning."));
		GetWorld()->GetTimerManager().ClearTimer(SegmentedCirclePercentageHandle);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(SegmentedCirclePercentageHandle,
	[this]()
	{ 
		if (SegmentedPercentage <= 1)
		{
			SegmentedPercentage += 0.0006f;
			Segmented_Dynamic->SetScalarParameterValue("SegmentPercentage", SegmentedPercentage);
			// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: SegmentedMotionAnimation started with SegmentedMotionPosition `%f`."), SegmentedMotionPosition);
		}
		else
		{
            GetWorld()->GetTimerManager().ClearTimer(SegmentedCirclePercentageHandle);
            return;
		}
	},
	0.01f, true);
}

void UUMG_ContentViewer::RE_OuterCircleAnimation()
{
	if (!OuterCircle_Dynamic)
	{
		GetWorld()->GetTimerManager().ClearTimer(OuterCircleAnimationHandle);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(OuterCircleAnimationHandle,
	[this]()
	{
		if (bIsIncreasing)
		{
			if (OuterCirclePosition <= 0.35)
			{
				OuterCirclePosition += 0.002f;
				OuterCircle_Dynamic->SetScalarParameterValue("Outer_SegmentPosition", OuterCirclePosition);
				// UE_LOG(LogTemp, Warning, TEXT("AContentViewer::OuterCircleAnimation: Incremented SegmentedMotionPosition `%f`."), OuterCirclePosition);
			}
			else
			{
				bIsIncreasing = false;
				// UE_LOG(LogTemp, Warning, TEXT("AContentViewer::OuterCircleAnimation: Boolean state id `&d`"), bIsIncreasing)
			}
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("AContentViewer::OuterCircleAnimation: Boolean state id `%d`"), bIsIncreasing)
			if (OuterCirclePosition > 0.0f)
			{
				OuterCirclePosition -= 0.002f;
				OuterCircle_Dynamic->SetScalarParameterValue("Outer_SegmentPosition", OuterCirclePosition);
				// UE_LOG(LogTemp, Warning, TEXT("UEmissionController::SegmentedMotionAnimation: Decremented SegmentedMotionPosition `%f`."), OuterCirclePosition);
			}
			else
			{
				bIsIncreasing = true;
			}
		}
	},
	0.01f, true);
}
