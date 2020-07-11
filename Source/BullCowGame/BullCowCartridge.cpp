// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); // Setting up game

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug line

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // If game is over then do ClearScreen() and SetupGame() the game
    if(bGameOver )
    {
        ClearScreen();   // clear terminal after enter input
        SetupGame();
    }
    else // else Checking PlayerGuess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
     
    HiddenWord = TEXT("cakes"); // Set he HiddenWord
    Lives = HiddenWord.Len();  // Set lives
    bGameOver = false; // Prompt player for guess

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); // Magic number Remove!
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in you guess and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // Check if guess won or not
    if(Guess == HiddenWord){

        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    // check if isogram
    // if(!IsIsogram)
    // {

    //     PrintLine(TEXT("No repeating letters, guess again"));
    //     return;
    // }

    // Prompt to guess again
    // check right number of characters
    // Prompt to guess again
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again| \nyou have %i lives remaming"), Lives);
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
    PrintLine(TEXT("Guess again, you have %i live left"), Lives);
}