#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include "Framework\timer.h"
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;
extern StopWatch g_timer;
extern bool g_quitGame;

//initialising 
enum Keys
{
	//keys for user input
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,
    K_SPACE,
	K_BACKSPACE,
	K_ESCAPE,
	K_1, 
	K_2,
	K_3,
	K_4,
	K_5, 
    K_COUNT
};
enum GAMESTATE 
{
	Mainmenu,
	Startgame,
	Gamemode,
	Instructions,
	Options,
	Credits,
	Gameover,
	Pausescreen,
	Exit
};
enum DIFFICULTY
{
	Easy,
	Medium,
	Hard,
	None
};
void init();  // initialize your variables, allocate memory, etc

//GAME UPDATE      
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console


// GAME FUNCTIONS & FEATURES
void gameHUD();
void renderWords();
void matchWords();
void airPlane();
void projectile();
void gameOver();

// GAME MENU & SELECTIONS
void gameTitle();
void mainMenu(); //main menu state	
void difficulty(); // difficulty level
void startGame(); // start game
void instructions(); //instruction state
void options(); //options states
void credits(); //credits state
void restartGame(); //restart game
void exitGame();
void pauseScreen();
void shutdown(); // do clean up, free memory

//DIFFICULTY
void easyMode();
void mediumMode();
void hardMode();

#endif // _GAME_H