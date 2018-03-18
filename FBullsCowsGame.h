/*Game logic is here*/
#include<string>
#pragma once


enum class EGuessStatus{Valid, NotIsogram, WrongLength};

struct FBullsCowsCount
{
	int Bulls = 0;
	int Cows = 0;
};

class FBullsCowsGame
{
public:
	FBullsCowsGame();
	void Reset();
	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(std::string&);
	FBullsCowsCount EvaluateValidGuess(std::string);

private:
	int MyMaxTries;
	int MyCurrentTry;
	std::string MyWord;
	bool bGameIsWon;

	bool IsIsogram(std::string) const;
};