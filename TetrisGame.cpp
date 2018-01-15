#include "TetrisGame.h"
#include "Line.h"
#include "Cube.h"
#include "Gun.h"
#include "Tee.h"
#include "Zigzag.h"
#include "Bomb.h"
#include "Joker.h"
#include "ScoreBar.h"
#include "Config.h"
#include "TetrisBoard.h"
#include <thread>
#include <chrono>


int TetrisGame:: MenuControl(char keyPressed, TetrisBoard& board, Score& scoreStatus) {

	switch (keyPressed) {
	
	case '1':
		if (!gameStarted) {
			setGameStarted();
			return runGame(board, scoreStatus);
		}
		break;
	case '2':
		if (gameStarted) {
			setGameStarted(); //prints the normal continue color
			return runGame(board, scoreStatus);
		}
		break;
	case '8':
		ShellExecute(0, 0, L"https://i.imgur.com/0u47UC2.jpg", 0, 0, SW_SHOW);
		return CONTINUE_GAME;
	case '9':
		printGameOver();
		return END_GAME;
	}
	_flushall();
	return CONTINUE_GAME;

}



void TetrisGame::continueBlink() {
	setTextColor(DARKGREY);
	gotoxy(16, 8);
	cout << "(2)";
	gotoxy(28, 8);
	cout << "CONTINUE";
	Sleep(200);

	setTextColor(WHITE);
	gotoxy(16, 8);
	cout << "(2)";
	gotoxy(28, 8);
	cout << "CONTINUE";
	Sleep(200);
}

void TetrisGame::hardDrop(Score & scoreStatus, int & timeInterval, unsigned long int & currentTime, int & minY, int & maxY)
{
	currentShape->getMinMaxShape(minY, maxY);
	scoreStatus.setDistance(currentShape, minY);
	scoreStatus.updateScoreValue(2 * scoreStatus.getDistance()); // hard drop 
	currentTime -= 800;
	timeInterval = 0;
}

void TetrisGame::createNewShape(int whichShape)
{
	
	switch (whichShape) {
	case Shape::CUBE:
		currentShape = new Cube;
		break;
	case Shape::LINE:
		currentShape = new Line;
		break;
	case Shape::GUN:
		currentShape = new Gun;
		break;
	case Shape::TEE:
		currentShape = new Tee;
		break;
	case Shape::ZIGZAG:
		currentShape = new Zigzag;
		break;
	case Shape::JOKER:
		currentShape = new Joker;
		break;
	case Shape::BOMB:
		currentShape = new Bomb;
		break;
	}
	
}

void TetrisGame::setGameStarted() {

	setTextColor(DARKGREY);
	gotoxy(16, 6);
	cout << "(1) START GAME";
	if (gameStarted) {
		setTextColor(LIGHTGREY);
		gotoxy(16, 8);
		cout << "(2)";
		gotoxy(28, 8);
		cout << "CONTINUE";
		return;
	}
	gameStarted = 1;
}

void TetrisGame::initGame(){

	TetrisBoard board;
	Score scoreStatus;
	setKeys();
	printMenu();
	displayBorder();
	scoreStatus.printScore();
	scoreStatus.printSpeed();
	scoreStatus.printParts();
	createNewShape(rand() % 5 + 10);


	while (true) // the game runs as long as the user doesn't press 9 or the game ends
	{
		char keyPressed;
		
		if (gameStarted)
			continueBlink();

		while (_kbhit())
		{
			keyPressed = _getch();
			if (MenuControl(keyPressed, board, scoreStatus) == END_GAME)
				return;
		}
	}

	
}

void TetrisGame::printMenu(){

	// STATUS BAR
	gotoxy(0, 0);
	cout << "Parts:     " << "Speed:         " << "  Score:  " << endl;
	for (int k = 0; k < 39; k++)
		cout << (unsigned char)175;

	// START - MENU BORDERS
	gotoxy(14,2);
	cout << (unsigned char)201;
	for (int k = 0; k < 23; k++)
		cout << (unsigned char)205;
	cout << (unsigned char)187 << endl;

	for (int j = 2; j < 17; j++){
		gotoxy(14, j+1);
		cout << (unsigned char)186;
		gotoxy(38, j + 1);
		cout << (unsigned char)186 << endl;
	}
	gotoxy(14, 18);
	cout << (unsigned char)200;
	for (int k = 0; k < 23; k++)
		cout << (unsigned char)205;
	cout << (unsigned char)188 << endl;
	// END MENU BORDERS

	// HEDLINE MENU
	gotoxy(23,3);
	cout << "M E N U" << endl;
	gotoxy(15, 4);
	for (int k = 0; k < 23; k++)
		cout << (unsigned char)175;
	
	gotoxy(16,6);
	cout << "(1) START GAME" ;
	gotoxy(16, 8);
	cout << "(2) PAUSE / CONTINUE" ;
	gotoxy(16, 10);
	cout << "(3) SPEED UP" ;
	gotoxy(16, 12);
	cout << "(4) SPEED DOWN";
	gotoxy(16, 14);
	cout << "(8) HELP!" ;
	gotoxy(16, 16);
	cout << "(9) EXIT";
}

void TetrisGame::printGameOver()
{
	setTextColor(LIGHTCYAN);
	gotoxy(0, 20);
	cout << "     _____                         ____                 " << endl;
	cout << "    / ____|                       / __ \\                " << endl;
	cout << "   | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ " << endl;
	cout << "   | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|" << endl;
	cout << "   | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   " << endl;
	cout << "    \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   " << endl;
	Sleep(3000);
}

bool TetrisGame::checkExit(char keyEntered)
{
	if (keyEntered == '9') {
		printGameOver();
		return true;
	}
	return false;
}

bool TetrisGame::checkPause(char keyEntered)
{
	if (keyEntered == '8') { // 'help'
		ShellExecute(0, 0, L"https://i.imgur.com/0u47UC2.jpg", 0, 0, SW_SHOW);
		return true;
	}
	else if (keyEntered == '2') { //'pause'
		Sleep(1000);
		return true;
	}
	return false;
}

void TetrisGame::displayBorder(){
	
	gotoxy(0, 3);

	for (int j = 2; j < 17; j++){
		cout << (unsigned char)186;
		gotoxy(11, j + 1);
		cout << (unsigned char)186 << endl;
	}

	cout << (unsigned char)200;
	for (int k = 0; k < 10; k++)
		cout << (unsigned char)205;
	cout << (unsigned char)188 << endl;

	cout << endl;
}

int TetrisGame::checkKeys(char ch){
	for (int i = 0; i < 11; i++){
		if (ch == keyboards[i])
			return i;
	}
	return invalid_Key;
}

void TetrisGame::setKeys()
{
	keyboards[0] = DOWN_KEY; 
	keyboards[1] = LEFT_KEY; 
	keyboards[2] = UP_KEY; 
	keyboards[3] = RIGHT_KEY; 
	keyboards[4] = SPACE_key;
	keyboards[5] = s_key;
	keyboards[6] = S_key;
	keyboards[7] = ONE;
	keyboards[8] = TWO;
	keyboards[9] = THREE;
	keyboards[10] = FOUR;
}

int TetrisGame::randomNum()
{
	int res = rand() % 100;
	if (res < 70)
		res = rand() % 5 + 10;
	else
		res = rand() % 2 + 15;
	return  res;
}

int TetrisGame::runGame(TetrisBoard& board, Score& scoreStatus) {
	int maxY, minY, timeInterval, gameStatus;
	int whichShape = currentShape->getShape(); // update 
	updateInterval(timeInterval, scoreStatus);

	while (true)
	{
		 gameStatus = dropInterval(board, scoreStatus, timeInterval, minY, maxY);
		 if (gameStatus==END_GAME || gameStatus==PAUSED)  return gameStatus; // the game will continue unless the pause or exit button has been pressed
		
		 //additional tests for the shapes, if it can move/detonate (the bomb).
		 if (gameStatus != TetrisBoard::BOMB_EXPLODED && gameStatus != TetrisBoard::STOP_JOKER) {
			 gameStatus = currentShape->move(Shape::DOWN, board);
		 }

		 //start a new round (creates new shapes and updates the board with the old one)
		 if(gameStatus == TetrisBoard::BOMB_EXPLODED || gameStatus==TetrisBoard::MOVE_FAIL || gameStatus == TetrisBoard::STOP_JOKER)
			 newRound(timeInterval, board, minY, maxY, scoreStatus, whichShape);

		 
	
		 if (board.checkEndGame()) {
				printGameOver();
				return END_GAME;
			}


	}
}

void TetrisGame::newRound(int& timeInterval, TetrisBoard& board, int& minY, int& maxY, Score& scoreStatus,int& whichShape) {
	updateInterval(timeInterval, scoreStatus);

	if (currentShape->getShape() != Shape::BOMB)
		board.updateBoard(currentShape);

	currentShape->getMinMaxShape(minY, maxY);
	scoreStatus.setLinesDeleted(board.deleteLines(currentShape, minY, maxY),currentShape); // deletes lines only within the shape's limit
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

void TetrisGame::changeSpeed(char indicator, int & timeInterval, Score & scoreStatus)
{
	if (indicator == THREE) // increase speed
		scoreStatus.increaseSpeed();
	else // decrease speed
		scoreStatus.decreaseSpeed();
	updateInterval(timeInterval, scoreStatus);

	scoreStatus.printSpeed();
}

int TetrisGame:: dropInterval(TetrisBoard& board, Score& scoreStatus, int& timeInterval, int&minY, int& maxY)
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
 
				else if (currentShape->getShape() == Shape::BOMB && (keyEntered == LEFT_KEY || keyEntered == RIGHT_KEY) && currentShape->shape[0].getX() > Point::START_Y-1 && currentShape->shape[0].getX() < COLUMN) { 					
					if(currentShape->move(validKey, board)==TetrisBoard::BOMB_EXPLODED){
						return TetrisBoard::BOMB_EXPLODED;
					}
				}


			}
		}
	}

	return 0;

}
