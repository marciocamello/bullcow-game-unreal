// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    Isograms = GetValidWords(Words);

    SetupGame(); // Setting up game
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    // If game is over then do ClearScreen() and SetupGame() the game
    if(bGameOver )
    {
        ClearScreen();   // clear terminal after enter input
        SetupGame();
    }
    else // else Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
     
    HiddenWord =Isograms[FMath::RandRange(0, Isograms.Num() - 1)]; // Set he HiddenWord
    Lives = HiddenWord.Len() * 2;  // Set lives
    bGameOver = false; // Prompt player for guess

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); // Magic number Remove!
    //PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug line
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in you guess and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Check if guess won or not
    if(Guess == HiddenWord){

        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    // Prompt to guess again
    // check right number of characters
    // Prompt to guess again
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again| \nyou have %i lives remaming"), Lives);
        return;
    }

    // check if isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Remove life
    PrintLine(TEXT("Lost a live!"));
    --Lives;

    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    // show the player Bulls and Cows
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
    PrintLine(TEXT("Guess again, you have %i live left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    // int32 Index = 0;
    // int32 Comparison = Index + 1;
    for ( int32 Index = 0; Index < Word.Len(); Index++)
    {
        for ( int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
    
    // For each letter
    // Start at element [0]
    // Compare agains the next letter
    // Until we reach [Guess.Leng() - 1]
    // if any the same return false
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    // for every index Guess is same as index hidden, BullCount++
    // if not a bull was it a cow? it yes CowCount++

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
           Count.Bulls ++;
           continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows ++;
                break;
            }
        }
    }

    return Count;
}
