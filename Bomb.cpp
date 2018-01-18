#include "Bomb.h"
#include "TetrisBoard.h"
#include "ScoreBar.h"

Bomb::Bomb()
{
	SIZE = 1;
	shape[0].setY(Point::START_Y);
	shape[0].setX(Point::START_X);
	setTextColor(whichColor(BOMB));
	setShape(BOMB);
	setTexture('@');
}

int Bomb::move(int direction, TetrisBoard& board)  {

	if (checkBomb(direction, board)) // the bomb needs to explode
		return TetrisBoard::BOMB_EXPLODED;
	
	for (int j = 0; j < SIZE; j++)
		shape[j].draw(BLANK_SPACE);

	if (direction != UP) { // the shape won't rotate
		for (int j = 0; j < SIZE; j++)
			shape[j].move(direction);
	}

	setTextColor(whichColor());
	for (int j = 0; j < SIZE; j++)
		shape[j].draw(getTexture());

	return TetrisBoard::MOVED_SUCCESSFULLY;
}

bool Bomb::checkBomb(int direction, TetrisBoard& board) {
	int x = shape[0].getX(), y = shape[0].getY();
	shape[0].draw(getTexture());

	// checks if the bomb can explode in the direction entered
	if ((direction == LEFT && board.checkBoard(x - 1, y) == true) ||
		(direction == RIGHT && board.checkBoard(x + 1, y) == true) ||
		(board.checkBoard(x, y + 1) == true) || y >= Board_Gap + ROWS - 1)
	{
		board.sethowManyDeleted(activateBomb(x, y, board)); // update the pieces that have been blown
		return true;
	}
	gotoxy(x, y);
	return false;
}

int Bomb::activateBomb(int x, int y, TetrisBoard& board) {
	int tempX, tempY = y - 1, howManyBombed = 0;
	for (int i = 0; i < EXPLOSION_AREA; i++)
	{
		tempX = x - 1;
		for (int j = 0; j < EXPLOSION_AREA; j++) {
			// if it's within the board limits and a shape has been met, update the counter (howManyBombed)
			if (tempX > 0 && tempX <= COLUMNS && tempY > Board_Gap && tempY < ROWS + Board_Gap) {
				if (board.getCoord(tempX, tempY))
					howManyBombed++;

				// explosion effect
				if (j % 2 == 0)
					setTextColor(YELLOW);
				else
					setTextColor(RED);
				gotoxy(tempX, tempY);
				cout << "*";
				Sleep(50);

				gotoxy(tempX, tempY);
				cout << BLANK_SPACE;
				board.setCoord(tempX, tempY, 0);
			}
			tempX++;
		}
		tempY++;
	}
	return howManyBombed;
}
