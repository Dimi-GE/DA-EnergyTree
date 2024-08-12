// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentActor.h"
// Utilities
#include "Misc/Paths.h"
#include "Engine/Texture2D.h"
// Multimedia
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "FileMediaSource.h"

// Sets default values
AParentActor::AParentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParentActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParentActor::SetUpMediaPlayers()
{
	if(MediaPlayer1)
	{
		MediaPlayer1->OpenSource(MediaSource1);
		MediaPlayer1->Play();
		UE_LOG(LogTemp, Log, TEXT("AParentActor::BeginPlay: MediaPlayer1 is set."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AParentActor::BeginPlay: MediaPlayer1 is nullptr - returnung."));
		return;
	}

	if (MediaPlayer2)
	{
		MediaPlayer2->OpenSource(MediaSource2);
		MediaPlayer2->Play();
		UE_LOG(LogTemp, Log, TEXT("AParentActor::BeginPlay: MediaPlayer2 is set."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AParentActor::BeginPlay: MediaPlayer2 is nullptr - returnung."));
		return;
	}
}