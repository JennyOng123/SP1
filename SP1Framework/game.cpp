// This is the main file for the game logic and function
//
//
#include "game.h"
#include "gamefunction.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Console size, width by heightt
COORD ConsoleSize = {100, 80};

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

// Game specific variables here
COORD charLocation;
int wordsZapped =0,score =0, CDtimer = 30 ,modeSelection=4,multiply=0;
int speed1,speed2,speed3,speed4;
COORD wordLocation1, wordLocation2, wordLocation3, wordLocation4, airplaneLoc,projectileLoc;
COORD c;
vector<string> words;
string line, userInput, playerName;
GAMESTATE GameState;
DIFFICULTY Difficulty;


void init()
{
	//Set game State
	GameState = Mainmenu;
	Difficulty = None;
	playerName = "";
	wordsZapped =0;
	score =0;
	multiply =0;
	words.clear();

	initConsole(ConsoleSize, "T Y P I E");

	// set the userInput textfield location to start game state.
	charLocation.X = ConsoleSize.X / 2-5;
	charLocation.Y = 60;

	// setting the location of the words.
	wordLocation1.X =  ConsoleSize.X/10;
	wordLocation1.Y =  1;
	wordLocation2.X = wordLocation1.X+18;
	wordLocation2.Y =  1;
	wordLocation3.X = wordLocation2.X+18;
	wordLocation3.Y =  1;
	wordLocation4.X = wordLocation3.X+18;
	wordLocation4.Y =  1;

	//setting airplane & projectile location
	airplaneLoc.X = (ConsoleSize.X/2)-5;
	airplaneLoc.Y = 52;
	projectileLoc.X = airplaneLoc.X+6;
	projectileLoc.Y = airplaneLoc.Y;


	//set dropping speed
	speed1=rand() % 2 + 1;
	speed2=rand() % 2 + 1;
	speed3=rand() % 2 + 1;
	speed4=rand() % 2 + 1;

	elapsedTime = 0.0;
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	shutDownConsole();
}

//GAME MENU AND SELECTIONS
void mainMenu()
{
	gameTitle();
	c.X= 26;
	c.Y = 24;
	//render menu
	writeToBuffer(c, "Start Game -------------------------------- [1]");
	c.Y+=2;
	writeToBuffer(c, "How to play ------------------------------- [2]");
	c.Y+=2;
	writeToBuffer(c, "Options ----------------------------------- [3]");
	c.Y+=2;
	writeToBuffer(c, "Credits ----------------------------------- [4]");
	c.Y+=2;
	writeToBuffer(c, "Quit Game --------------------------------- [5]");	
}
void difficulty()
{
	//render menu
	c.X=25;
	c.Y= 25;
	writeToBuffer(c,"EASY ---------------------------------------- [1]");
	c.Y+=2;
	writeToBuffer(c,"MEDIUM -------------------------------------- [2]");
	c.Y+=2;
	writeToBuffer(c,"HARD ---------------------------------------- [3]");

	switch(Difficulty)
	{
	case Easy: easyMode();
		break;
	case Medium: mediumMode();
		break;
	case Hard: hardMode();
		break;
	}
}
void startGame()
{
	SetConsoleTitle(L"TYPIE THE GAME");
	//HUD
	gameHUD();

	//render words
	renderWords();

	//render airplane
	airPlane();
}
void instructions()
{
	c.X=20;
	c.Y=5;
	string data;
	SetConsoleTitle(L"INSTRUCTIONS");
	ifstream myfile("instruction.txt");
	if(myfile.is_open())
	{
		while(getline(myfile, data))
		{
			writeToBuffer(c,data);
			c.Y++;
		}
	}
	myfile.close();
}
void options()
{
	SetConsoleTitle(L"OPTIONS");
}
void credits()
{
	SetConsoleTitle(L"CREDITS");
	c.X=20;
	c.Y=5;
	string data;
	ifstream myfile("credits.txt");
	if(myfile.is_open())
	{
		while(getline(myfile, data))
		{
			writeToBuffer(c,data);
			c.Y++;
		}
	}
	myfile.close();
}
void restartGame()
{
	wordsZapped =0;
	score = 0;
	multiply =0;
	CDtimer = 30;
	elapsedTime = 0.0;
	words.clear();
	wordLocation1.Y =1;
	wordLocation2.Y =1;
	wordLocation3.Y =1;
	wordLocation4.Y =1;
	airplaneLoc.X = (ConsoleSize.X/2)-5;

	//check previous mode
	switch(modeSelection)
	{
	case 1: easyMode();
		break;
	case 2: mediumMode();
		break;
	case 3: hardMode();
		break;
	}
}
void exitGame()
{
	g_quitGame = true;
}
void pauseScreen()
{
	gameHUD();
	c.X=(ConsoleSize.X/2)-25;
	c.Y=20;
	//render pause menu
	writeToBuffer(c,"Resume ----------------------------------------- [1]");
	c.Y+=2;
	writeToBuffer(c,"Restart ---------------------------------------- [2]");
	c.Y+=2;
	writeToBuffer(c,"Back to main menu -------------------------------[3]");
}

//UPDATE FUNCTIONS
void getInput()
{    
	keyPressed[K_A] = isKeyPressed(0X41);
	keyPressed[K_B] = isKeyPressed(0X42);
	keyPressed[K_C] = isKeyPressed(0X43);
	keyPressed[K_D] = isKeyPressed(0X44);
	keyPressed[K_E] = isKeyPressed(0X45);
	keyPressed[K_F] = isKeyPressed(0X46);
	keyPressed[K_G] = isKeyPressed(0X47);
	keyPressed[K_H] = isKeyPressed(0X48);
	keyPressed[K_I] = isKeyPressed(0X49);
	keyPressed[K_J] = isKeyPressed(0X4A);
	keyPressed[K_K] = isKeyPressed(0X4B);
	keyPressed[K_L] = isKeyPressed(0X4C);
	keyPressed[K_M] = isKeyPressed(0X4D);
	keyPressed[K_N] = isKeyPressed(0X4E);
	keyPressed[K_O] = isKeyPressed(0X4F);
	keyPressed[K_P] = isKeyPressed(0X50);
	keyPressed[K_Q] = isKeyPressed(0X51);
	keyPressed[K_R] = isKeyPressed(0X52);
	keyPressed[K_S] = isKeyPressed(0X53);
	keyPressed[K_T] = isKeyPressed(0X54);
	keyPressed[K_U] = isKeyPressed(0X55);
	keyPressed[K_V] = isKeyPressed(0X56);
	keyPressed[K_W] = isKeyPressed(0X57);
	keyPressed[K_X] = isKeyPressed(0X58);
	keyPressed[K_Y] = isKeyPressed(0x59);
	keyPressed[K_Z] = isKeyPressed(0x5A);
	keyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_1] = isKeyPressed('1');
	keyPressed[K_2] = isKeyPressed('2');
	keyPressed[K_3] = isKeyPressed('3');
	keyPressed[K_4] = isKeyPressed('4');
	keyPressed[K_5] = isKeyPressed('5');
}
void update(double dt)
{
	//Check keypressed
	if (keyPressed[K_A])
	{
		userInput+="A";
		matchWords();
	}
	if (keyPressed[K_B])
	{
		userInput+="B";
		matchWords();
	}
	if (keyPressed[K_C])
	{
		userInput+="C";
		matchWords();
	}
	if (keyPressed[K_D])
	{
		userInput+="D";
		matchWords();
	}
	if (keyPressed[K_E])
	{
		userInput+="E";
		matchWords();
	}
	if (keyPressed[K_F])
	{
		userInput+="F";
		matchWords();
	}
	if (keyPressed[K_G])
	{
		userInput+="G";
		matchWords();
	}
	if (keyPressed[K_H])
	{
		userInput+="H";
		matchWords();
	}
	if (keyPressed[K_I])
	{
		userInput+="I";
		matchWords();
	}
	if (keyPressed[K_J])
	{
		userInput+="J";
		matchWords();
	}
	if (keyPressed[K_K])
	{
		userInput+="K";
		matchWords();
	}
	if (keyPressed[K_L])
	{
		userInput+="L";
		matchWords();
	}
	if (keyPressed[K_M])
	{
		userInput+="M";
		matchWords();
	}
	if (keyPressed[K_N])
	{
		userInput+="N";
		matchWords();
	}
	if (keyPressed[K_O])
	{
		userInput+="O";
		matchWords();
	}
	if (keyPressed[K_P])
	{
		userInput+="P";
		matchWords();
	}
	if (keyPressed[K_Q])
	{
		userInput+="Q";
		matchWords();
	}
	if (keyPressed[K_R])
	{
		userInput+="R";
		matchWords();
	}
	if (keyPressed[K_S])
	{
		userInput+="S";
		matchWords();
	}
	if (keyPressed[K_T])
	{
		userInput+="T";
		matchWords();
	}
	if (keyPressed[K_U])
	{
		userInput+="U";
		matchWords();
	}
	if (keyPressed[K_V])
	{
		userInput+="V";
		matchWords();
	}
	if (keyPressed[K_W])
	{
		userInput+="W";
		matchWords();
	}
	if (keyPressed[K_X])
	{
		userInput+="X";
		matchWords();
	}
	if (keyPressed[K_Y])
	{
		userInput+="Y";
		matchWords();
	}
	if (keyPressed[K_Z])
	{
		userInput+="Z";
		matchWords();
	}
	if(keyPressed[K_BACKSPACE])
	{
		if(userInput.size()>0){
			userInput.pop_back();
		}
	}
	if(GameState == Mainmenu)
	{
		if(keyPressed[K_1])
			GameState = Gamemode;
		if(keyPressed[K_2])
			GameState = Instructions;
		if(keyPressed[K_3])
			GameState = Options;
		if(keyPressed[K_4])
			GameState = Credits;
		// quits the game if player hits the escape key
		if (keyPressed[K_5])
			GameState = Exit;
	}
	else if (GameState == Gamemode)
	{
		if(keyPressed[K_1])
			Difficulty = Easy;
		if(keyPressed[K_2])
			Difficulty = Medium;
		if(keyPressed[K_3])
			Difficulty = Hard;
	}
	else if (GameState == Instructions)
	{
		if(keyPressed[K_1])
			GameState = Mainmenu;
	}
	else if (GameState == Credits)
	{
		if(keyPressed[K_1])
			GameState = Mainmenu;
	}
	else if(GameState == Startgame)
	{
		if(keyPressed[K_SPACE])
		{
			// Clear user input.
			userInput="";
			multiply =0;
		}
		if (keyPressed[K_ESCAPE])
		{
			GameState = Pausescreen;
		}
		// Start time elapsed when the game starts.
		elapsedTime += dt;
		deltaTime = dt;
	}

	else if(GameState == Pausescreen)
	{
		if(keyPressed[K_1])
			GameState = Startgame;
		if(keyPressed[K_2])
			restartGame();
		if(keyPressed[K_3])
			init();
	}
	else if (GameState == Gameover)
	{
		if(keyPressed[K_1])
			restartGame();
		if(keyPressed[K_2])
			init();
	} 
}
void render()
{    
	// Clears the buffer with this colour attribute
	clearBuffer(0x0);

	switch(GameState)
	{
	case Mainmenu: mainMenu();
		break;
	case Startgame: startGame();
		break;
	case Gamemode: difficulty();
		break;
	case Instructions: instructions();
		break;
	case Options: options();
		break;
	case Credits: credits();
		break;
	case Gameover: gameOver();
		break;
	case Pausescreen: pauseScreen();
		break;
	case Exit: exitGame();
		break;
	}
	// Set up sample colours, and output shadings
	const WORD colors[] =   {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};


	/*// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / deltaTime << "fps";
	c.X = ConsoleSize.X-9;
	c.Y = 0;
	writeToBuffer(c, ss.str());
	*/




	// Writes the buffer to the console, hence you will see what you have written
	flushBufferToConsole();
}

//functions
void gameHUD()
{
	std::ostringstream ss;
	//render number of words typed
	ss.str("");
	ss << wordsZapped;
	c.X = 82;
	c.Y=0;
	writeToBuffer(c,"Word zapped: ");
	c.X = 95;
	writeToBuffer(c,ss.str());
	//render score
	ss.str("");
	ss << score;
	c.X = 69;
	writeToBuffer(c,"Score: ");
	c.X = 76;
	writeToBuffer(c,ss.str());
	//render combo
	ss.str("");
	ss << multiply;
	c.X=2;
	writeToBuffer(c,"Combo: ");
	c.X=9;
	writeToBuffer(c,ss.str());

	//render timer
	ss.str("");
	ss << CDtimer-elapsedTime;
	c.X =15;
	writeToBuffer(c,"Time: ");
	c.X =20;
	writeToBuffer(c,ss.str());

	//print userinput
	writeToBuffer(charLocation,userInput);

	//check for time out
	if((CDtimer-elapsedTime) < 1)
	{
		elapsedTime = 0.0;
		CDtimer = 30;
		GameState = Gameover;
	}
}
void renderWords()
{
	wordLocation1.Y= moveWord(wordLocation1.Y,speed1);
	wordLocation2.Y= moveWord(wordLocation2.Y,speed2);
	wordLocation3.Y= moveWord(wordLocation3.Y,speed3);	
	wordLocation4.Y= moveWord(wordLocation4.Y,speed4);
	writeToBuffer(wordLocation1,words[0]);
	writeToBuffer(wordLocation2,words[1]);
	writeToBuffer(wordLocation3,words[2]);
	writeToBuffer(wordLocation4,words[3]);
}
void matchWords()
{
	if(userInput == words[0])
	{
		addScore(multiply, score, wordsZapped);
		clearWord(words,userInput,0);
		resetPosition(wordLocation1);
		setSpeed(speed1);
		airplaneLoc.X = wordLocation1.X-3;
	}

	else if(userInput == words[1])
	{
		addScore(multiply, score, wordsZapped);
		clearWord(words,userInput,1);
		resetPosition(wordLocation2);
		setSpeed(speed2);
		airplaneLoc.X = wordLocation2.X-3;
	}
	else if(userInput == words[2])
	{
		addScore(multiply, score, wordsZapped);
		clearWord(words,userInput,2);
		resetPosition(wordLocation3);
		setSpeed(speed3);
		airplaneLoc.X = wordLocation3.X-3;
	}
	else if(userInput == words[3])
	{
		addScore(multiply, score, wordsZapped);
		clearWord(words,userInput,3);
		resetPosition(wordLocation4);
		setSpeed(speed4);
		airplaneLoc.X = wordLocation4.X-3;
	}
	else
	{
		//doesent match
	}
} 

//Print to Screen
void airPlane()
{
	airplaneLoc.Y=52;
	writeToBuffer(airplaneLoc,"     /\\");
	airplaneLoc.Y++;
	writeToBuffer(airplaneLoc,"__   ||   __");
	airplaneLoc.Y++;
	writeToBuffer(airplaneLoc,"||  /••\\  ||");
	airplaneLoc.Y++;
	writeToBuffer(airplaneLoc,"| \\/••••\\/ |");
	airplaneLoc.Y++;
	writeToBuffer(airplaneLoc,"\\__'####'__/");
	airplaneLoc.Y++;
	writeToBuffer(airplaneLoc,"   \\____/");
}
void projectile()
{
	//spawn project tile
}
void gameOver()
{
	//gameover screen
	gameHUD();
	c.X=ConsoleSize.X/2-5;
	c.Y = ConsoleSize.Y/2;
	writeToBuffer(c,"G A M E O V E R");
	c.Y+=2;
	writeToBuffer(c,"Retry?     [1]");
	c.Y+=1;
	writeToBuffer(c,"Main Menu  [2]");
}
void gameTitle()
{	
	c.X= 25;
	c.Y = 10;
	string data;
	ifstream myfile("TYPIE.txt");
	if(myfile.is_open())
	{
		while(getline(myfile, data))
		{
			writeToBuffer(c,data);
			c.Y++;
		}
	}
	myfile.close();
}

//Difficulty
void easyMode()
{
	modeSelection = 1;
	int i =0;
	ifstream myfile ("easy.txt");
	if(myfile.is_open())
	{
		while(getline(myfile, line))
		{
			words.push_back(line);
			i++;
		}
		myfile.close();
	}
	else
	{
		g_quitGame = true;
	}
	GameState = Startgame;
}
void mediumMode()
{
	modeSelection = 2;
	int i =0;
	ifstream myfile ("medium.txt");
	if(myfile.is_open())
	{
		while(getline(myfile, line))
		{
			words.push_back(line);
			i++;
		}
		myfile.close();
	}
	else
	{
		g_quitGame = true;
	}
	GameState = Startgame;
}
void hardMode()
{
	modeSelection = 3;
	int i =0;
	ifstream myfile ("hard.txt");
	if(myfile.is_open())
	{
		while(getline(myfile, line))
		{
			words.push_back(line);
			i++;
		}
		myfile.close();
	}
	else
	{
		g_quitGame = true;
	}
	GameState = Startgame;
}