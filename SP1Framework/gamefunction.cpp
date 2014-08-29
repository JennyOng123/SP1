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

void matchWord(vector<string>& word, string& input)
{
			input ="";
			iter_swap ( word.begin() , word.begin()+4 );
			word.erase(word.begin()+4);
}
