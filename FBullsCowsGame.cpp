#include "FBullsCowsGame.h"
#include<iostream>
#include<map>
#pragma once

FBullsCowsGame::FBullsCowsGame()
{
	Reset();
}

void FBullsCowsGame::Reset()
{
	MyCurrentTry = 1;
	MyMaxTries = 7;
	MyWord = "camp"; //the word must be an isogram
	bGameIsWon = false;
}

int FBullsCowsGame::GetMaxTries() const
{
	return MyMaxTries;
}

int FBullsCowsGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int FBullsCowsGame::GetWordLength() const
{
	return MyWord.size();
}

bool FBullsCowsGame::IsGameWon() const
{
	return bGameIsWon;
}


EGuessStatus FBullsCowsGame::CheckGuessValidity(std::string& Guess)
{
	if (Guess.size() != GetWordLength())
	{
		return EGuessStatus::WrongLength;
	}

	for (char& Letter : Guess)
	{
		Letter = tolower(Letter);
	}

	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram;
	}
	return EGuessStatus::Valid;
}

//checks how many bulls and cows are in the user guess
FBullsCowsCount FBullsCowsGame::EvaluateValidGuess(std::string Guess)
{
	++MyCurrentTry;
	FBullsCowsCount BullsCowsInGuess;
	for (int i = 0; i < MyWord.size(); ++i)
	{
		for (int j = 0; j < MyWord.size(); ++j)
		{
			if (Guess[i] == MyWord[i])
			{
				++BullsCowsInGuess.Bulls;
				break;
			}
			else if (Guess[i] == MyWord[j])
			{
				++BullsCowsInGuess.Cows;
				break;
			}
		}
	}
	if (BullsCowsInGuess.Bulls == GetWordLength())
	{
		bGameIsWon = true;
	}
	
	return BullsCowsInGuess;
}

bool FBullsCowsGame::IsIsogram(std::string Guess) const
{
	std::map<char, bool> EncounteredLetters;
	for (char Letter : Guess)
	{
		if (EncounteredLetters[Letter])
		{
			return false;
		}
		else
		{
			EncounteredLetters[Letter] = true;
		}
	}
	return true;
}
