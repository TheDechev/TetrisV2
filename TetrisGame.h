#ifndef _Tetris_Game
#define _Tetris_Game
#include "ScoreBar.h"
#include <iostream>
using namespace std;

#define ROW 15
#define COLUMN 10


class TetrisGame
{
	enum { invalid_Key = -1, ESC = 27, SPACE_key = 32, s_key = 115, S_key = 83, ONE = 49, TWO = 50, THREE = 51, FOUR = 52, DOWN_KEY = 80, LEFT_KEY = 75, UP_KEY = 72, RIGHT_KEY = 77 };
	enum { PAUSED = 78, PLAYING, END_GAME, CONTINUE_GAME = 0 };

	Shape* currentShape;
	char keyboards[11];
	int Board[COLUMN][ROW], gameStarted = 0;
public:
	void setGameStarted(); 

	void displayBorder() const;

	int runGame(TetrisBoard& board, Score& scoreStatus);

	// The function initializing the game
	void initGame();

	// The function is getting a key and cheaks if its valid key
	int checkKeys(char ch) const;

	void setKeys();

	int randomNum() const;

	int dropInterval(TetrisBoard& board, Score& scoreStatus, int& timeInterval, int&minY, int& maxY);

	void printMenu();

	void printGameOver() const;

	bool checkExit(char keyEntered) const;

	bool checkPause(char keyEntered) const;

	void newRound(int& timeInterval, TetrisBoard& board, int& minY, int& maxY, Score& scoreStatus, int& whichShape);

	void changeSpeed(char indicator, int& timeInterval, Score& scoreStatus);

	int MenuControl(char keyPressed, TetrisBoard& board, Score& scoreStatus);

	void continueBlink();

	void updateInterval(int& timeInterval, Score& scoreStatus) { timeInterval = 800 - 300 * scoreStatus.getSpeed();}

	void hardDrop(Score& scoreStatus, int& timeInterval, unsigned long int& currentTime, int& minY, int& maxY);

	void createNewShape(int whichShape);
};

#endif