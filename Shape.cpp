
#include "GoToXY.h"
#include "TetrisBoard.h"
#include "Cube.h"
#include "Line.h"




bool Shape::canTheShapeRotate(const TetrisBoard& board) {
	int x, y;
	for (int i = 0; i < SIZE; i++) //checks if the current shape has reached the bottom of the screen or near another shape
	{
		x = shape[i].getX();
		y = shape[i].getY();
		if (y >= Board_Gap + ROWS - 1 || board.checkBoard(x, y + 1)
			|| (board.checkBoard(x + 1, y) && board.checkBoard(x - 1, y)) // close to shapes in both sides left+right
			|| (board.checkBoard(x + 2, y) && board.checkBoard(x - 1, y))
			|| (board.checkBoard(x + 1, y) && board.checkBoard(x - 2, y))
			|| (x >= COLUMNS - 2 && board.checkBoard(x - 1, y)) // close to a wall from the right + a shape in the left
			|| (x <= 1 && board.checkBoard(x + 1, y))) // close to a wall in the left + a shape in the right
			return false;
	}
	return true;
}



int Shape::move(int direction, TetrisBoard& board) {
	
	int degree = getDegree();
	int check = 1;


	if (!(board.checkPos(this, direction) == TetrisBoard::FREE_SPACE))
		return TetrisBoard::MOVE_FAIL;

	for (int j = 0; j < SIZE; j++)
		shape[j].draw(' ');

	if (direction != UP) { // the shape won't rotate
		for (int j = 0; j < SIZE; j++)
			shape[j].move(direction);
	}

	setTextColor(whichColor());
	for (int j = 0; j < SIZE; j++)
		shape[j].draw(getTexture());

	return TetrisBoard::MOVED_SUCCESSFULLY;

}




void Shape::getMinMaxShape(int& minY, int& maxY) {
	minY = maxY = shape[0].getY();
	for (int i = 1; i < SIZE; i++) {
		if (shape[i].getY() > minY)
			minY = shape[i].getY();
		if (shape[i].getY()< maxY)
			maxY = shape[i].getY();
	}
}

Color Shape::whichColor(int theShapeNum) const {
	
		if (theShapeNum == 9999)
			theShapeNum = shapeType;
		switch (theShapeNum) {
		case CUBE:
			return LIGHTMAGENTA;
		case LINE:
			return LIGHTCYAN;
		case JOKER:
			return YELLOW;
		case BOMB:
			return LIGHTRED;
		case ZIGZAG:
			return GREEN;
		case TEE:
			return LIGHTGREEN;
		case GUN:
			return LIGHTBLUE;
		default:
			return GREEN;
		}

}
