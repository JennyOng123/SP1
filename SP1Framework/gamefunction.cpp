#include "game.h"

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