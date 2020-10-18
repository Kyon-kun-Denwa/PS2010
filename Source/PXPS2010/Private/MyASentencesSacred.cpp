// Fill out your copyright notice in the Description page of Project Settings.


#include "MyASentencesSacred.h"
#include "Components/TextRenderComponent.h"


// Sets default values
AMyASentencesSacred::AMyASentencesSacred()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	TextRenderComponent->SetupAttachment(GetRootComponent());
	//TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetYScale(1.0f);
	TextRenderComponent->SetXScale(1.0f);
	TextRenderComponent->SetVisibility(true);
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
	/*
	FString projectDir = FPaths::ProjectContentDir();
	projectDir += "Sentences/Sacred.txt";
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*projectDir))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("** Could not Find File **"));
		return;
	}
	FFileHelper::LoadANSITextFileToStrings(*(projectDir), NULL, StringArray);

	SIndex = 0;*/
}

// Called when the game starts or when spawned
void AMyASentencesSacred::BeginPlay()
{
	Super::BeginPlay();

	//Read text file at run time, allows updates after adding blueprint in unreal editor
	FString projectDir = FPaths::ProjectContentDir();
	projectDir += "Sentences/Sacred.txt";
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*projectDir))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("** Could not Find File **"));
		return;
	}
	FFileHelper::LoadANSITextFileToStrings(*(projectDir), NULL, StringArray);

	float InitialTimer = 0.0f; //Delay before starting 1st array read in seconds
	float RepeatingTimer = 3.0f; //Delay between array reads in seconds
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyASentencesSacred::RepeatingFunction, RepeatingTimer, true, InitialTimer);
}

// Called every frame
void AMyASentencesSacred::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyASentencesSacred::RepeatingFunction()
{
	
	//random index based on array length
	SIndex = rand() % StringArray.Num();
	// Sets text to the next line.
	TextRenderComponent->SetText(FText::FromString(StringArray[SIndex]));
	
}

