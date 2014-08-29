#ifndef _GAMEFUNCTION_H
#define _GAMEFUNCTION_H


void addScore(int& combo, int& score, int& wordzapped);
int moveWord(int,int);
void matchWord(vector<string>& word, string& input);

#endif // _GAMEFUNCTION_H