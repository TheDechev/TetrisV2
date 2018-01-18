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

	void displayBorder();

	int runGame(TetrisBoard& board, Score& scoreStatus);

	// The function initializing the game
	void initGame();

	// The function is getting a key and cheaks if its valid key
	int checkKeys(char ch) const;

	void setKeys();

	int randomNum();

	int dropInterval(TetrisBoard& board, Score& scoreStatus, int& timeInterval, int&minY, int& maxY)
	{
		char keyEntered;
		int validKey, speed;
		unsigned long int currentTime;
		currentTime = (unsigned long int) GetTickCount64() + timeInterval; // the shape goes down every timeInerval ms

		while (GetTickCount64() <= currentTime) {
			if (_kbhit()) { // otherwise, check for an input
				keyEntered = _getch();
				_flushall();

				validKey = checkKeys(keyEntered); // checks if the pressed key is valid

				if (checkExit(keyEntered)) return END_GAME;
				if (checkPause(keyEntered)) return PAUSED;

				if (validKey != invalid_Key) {
					speed = scoreStatus.getSpeed();

					//increases or decreases the current speed if possible
					if ((keyEntered == THREE && speed < Score::VERY_HIGH) || (keyEntered == FOUR && speed > Score::VERY_SLOW)) {
						changeSpeed(keyEntered, timeInterval, scoreStatus);
						break;
					}


					// checks if there's a free space in the direction entered OR if it's a joker it'll also return true
					if (board.checkPos(currentShape, validKey) == TetrisBoard::FREE_SPACE)
					{
						// Space key has been pressed - hard drop
						if (keyEntered == SPACE_key)
							hardDrop(scoreStatus, timeInterval, currentTime, minY, maxY);

						//Stop the Joker
						else if (currentShape->getShape() == Shape::JOKER && (keyEntered == s_key || keyEntered == S_key))
						{
							board.updateBoard(currentShape);
							return TetrisBoard::STOP_JOKER;
						}

						//Down key has been pressed - soft drop
						else if (validKey == Shape::DOWN) {
							scoreStatus.updateScoreValue(1); // increases score by 1
							scoreStatus.printScore();
							setTextColor(currentShape->whichColor());
						}
						currentShape->move(validKey, board);
					}

					//check if the bomb needs to explode on the direction entered

					else if (currentShape->getShape() == Shape::BOMB && (keyEntered == LEFT_KEY || keyEntered == RIGHT_KEY) && currentShape->shape[0].getX() > Point::START_Y - 1 && currentShape->shape[0].getX() < COLUMN) {
						if (currentShape->move(validKey, board) == TetrisBoard::BOMB_EXPLODED) {
							return TetrisBoard::BOMB_EXPLODED;
						}
					}


				}
			}
		}

		return 0;

	}

	void printMenu();

	void printGameOver();

	bool checkExit(char keyEntered);

	bool checkPause(char keyEntered);

	void newRound(int& timeInterval, TetrisBoard& board, int& minY, int& maxY, Score& scoreStatus, int& whichShape) {
		updateInterval(timeInterval, scoreStatus);

		if (currentShape->getShape() != Shape::BOMB)
			board.updateBoard(currentShape);

		currentShape->getMinMaxShape(minY, maxY);
		scoreStatus.setLinesDeleted(board.deleteLines(currentShape, minY, maxY), currentShape); // deletes lines only within the shape's limit
		scoreStatus.updateScoreValue(scoreStatus.getLinesDeleted());
		scoreStatus.updateScoreValue(-50 * board.getHowManyDeleted()); // each block the bomb erased costs 50 points
		board.sethowManyDeleted(0);
		scoreStatus.printParts();
		scoreStatus.printScore();
		whichShape = randomNum();
		delete currentShape;
		createNewShape(whichShape); // creates a new shape randomly
		currentShape->move(Shape::DOWN, board);
	}

	void changeSpeed(char indicator, int& timeInterval, Score& scoreStatus);

	int MenuControl(char keyPressed, TetrisBoard& board, Score& scoreStatus);

	void continueBlink();

	void updateInterval(int& timeInterval, Score& scoreStatus) { timeInterval = 800 - 300 * scoreStatus.getSpeed();}

	void hardDrop(Score& scoreStatus, int& timeInterval, unsigned long int& currentTime, int& minY, int& maxY);

	void createNewShape(int whichShape);
};

#endif