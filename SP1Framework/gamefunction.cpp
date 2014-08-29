#include "game.h"
#include "gamefunction.h"

void addScore(int& combo, int& score, int& wordzapped)
{
	if(combo<10)
		combo++;
	wordzapped++;
	score += (combo*1);
}

int moveWord(int loc, int speed)
{
	if(loc<50)
	{
		loc+=speed;
		return loc;
	}
	else
		return 1;
}

void clearWord(vector<string>& word, string& input, int c)
{
	if(word.size() > 4)
	{
		input ="";
		iter_swap ( word.begin()+c , word.begin()+4 );
		word.erase(word.begin()+4);
	}
	else
	{
			input ="";
			word[c] ="";
	}
}

void resetPosition(COORD& wordLoc)
{
	wordLoc.Y=1;
}

void setSpeed(int& s)
{
	s =rand() % 2 + 1;
}