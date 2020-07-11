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
        // Check if guess won or not
        if(Input == HiddenWord){

            PrintLine(TEXT("You have Won!"));
            EndGame();
        }
        else
        {
            --Lives;
            PrintLine(TEXT("Lost a live!"));
            PrintLine(TEXT("%i"), Lives);

            if(Lives > 0)
            {
                if(Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("Sorry, try guessing again| \nyou have %i lives remaming"), Lives);
                }
            }
            else
            {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }
        }
    }

    // check if isogram
    // Prompt to guess again
    // check right number of characters
    // Prompt to guess again

    // Remove life

    // check if lives > 0
    // If yes PlayAgain
    // Chow lives left
    // If no show GameOver
    // Prompt to play again, Press enter to play again?
    // check user input
    // PlayAgain or Quit
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
    PrintLine(TEXT("Press enter to play again."));
}