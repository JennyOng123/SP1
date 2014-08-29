#ifndef _GAMEFUNCTION_H
#define _GAMEFUNCTION_H


void addScore(int& combo, int& score, int& wordzapped);
int moveWord(int,int);
void clearWord(vector<string>& word, string& input, int c);
void resetPosition(COORD& wordLoc);
void setSpeed(int& s);
#endif // _GAMEFUNCTION_H