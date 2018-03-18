/* It is the console executable that handles user interaction and controls the execution loop.
Game logic is in the FBullCowGame class.
*/
#include<iostream>
#include<string>
#include"FBullsCowsGame.h"
#pragma once
using std::cout;
using std::cin;
using std::endl;


void PrintIntro();
void PrintRules();
std::string GetGuess();
void PlayGame();
void PrintGameSummary();
bool IsReplay();
bool GetYesNoAnswer();

FBullsCowsGame Game; //instance is reused across plays

int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} while (IsReplay());
	return 0;
}

void PrintIntro()
{
	cout << "Welcome to the game of Bulls and Cows." << endl;
	PrintRules();
}

void PrintRules()
{
	cout << "I picked a " << Game.GetWordLength() << "-letter isogram (that is, a word without repeating letters)." << endl
		<< "Your goal is to guess which word I picked. You have " << Game.GetMaxTries() << " tries." << endl
		<< "I respond to your guess with the number of \"Cows\" and \"Bulls\"." << endl
		<< "\"Cow\" means a right letter is the wrong position, and \"Bull\" means a right letter in the right position." << endl
		<< "Good luck!" << endl;
}

//controls one play of the game
void PlayGame()
{
	Game.Reset();
	do
	{
		std::string Guess = GetGuess();
		FBullsCowsCount Result = Game.EvaluateValidGuess(Guess);
		cout << "Bulls: " << Result.Bulls << endl << "Cows: " << Result.Cows << endl;
	} while (!Game.IsGameWon() && Game.GetCurrentTry() <= Game.GetMaxTries());
	PrintGameSummary();
}

std::string GetGuess()
{
	do
	{
		//getting input from the user
		cout << endl << "Try " << Game.GetCurrentTry() << " of " << Game.GetMaxTries() << ". Enter your guess: ";//no endl so user could enter their guess on this line because it looks good
		std::string Guess;
		std::getline(cin, Guess);

		//checking whether the input is valid and give appropriate feedback if it's not. Loop until valid input is given
		EGuessStatus Status = Game.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::WrongLength:
			cout << "Please enter a " << Game.GetWordLength() << "-letter word." << endl;
			break;
		case EGuessStatus::NotIsogram:
			cout << "Please enter a word without repeating letters." << endl;
			break;
		default:
			return Guess;
		}
	} while (true); //loop breaks when valid Guess is returned from the inside of the switch statement
}

void PrintGameSummary()
{
	if (Game.IsGameWon())
	{
		cout << endl << "Congratulations! You won!" << endl;
	}
	else
	{
		cout << endl << "You don't have any more tries." << endl;
	}
}

bool IsReplay()
{
	bool bReplay = false;
	cout << "Do you want to play again (y/n)?" << endl;
	if (Game.IsGameWon())
	{
		cout << "Keep in mind that the word is the same each time you play the game." << endl;
	}
	bReplay = GetYesNoAnswer();

	if (bReplay && !Game.IsGameWon())
	{
		cout << "Do you want me to repeat the rules (y/n)?" << endl;
		if (GetYesNoAnswer())
		{
			cout << endl;
			PrintRules();
		}
	}
	return bReplay;
}

bool GetYesNoAnswer()
{
	do
	{
		std::string Response;
		std::getline(cin, Response);
		if (Response == "yes" || Response == "y")
		{
			return true;
		}
		else if (Response == "no" || Response == "n")
		{
			return false;
		}
		else
		{
			cout << "Please enter either 'y' or 'n'." << endl;
		}
	} while (true); //loop breaks from inside if understandable input is given
}
