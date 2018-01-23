
#include "GoToXY.h"
#include "TetrisBoard.h"
#include "Cube.h"
#include "Line.h"

//bool Shape::canTheShapeRotate(const TetrisBoard& board) {
//	int x, y;
//	for (int i = 0; i < SIZE; i++) //checks if the current shape has reached the bottom of the screen or near another shape
//	{
//		x = shape[i].getX();
//		y = shape[i].getY();
//		if  (   y >= Board_Gap + ROWS - 1 || board.checkBoard(x, y + 1)
//			|| (board.checkBoard(x + 1, y) && board.checkBoard(x - 1, y)) // close to shapes in both sides left+right
//			|| (board.checkBoard(x + 2, y) && board.checkBoard(x - 1, y))
//			|| (board.checkBoard(x + 1, y) && board.checkBoard(x - 2, y))
//			|| (x >= COLUMNS - 2 && board.checkBoard(x - 1, y)) // close to a wall from the right + a shape in the left
//			|| (x <= 1 && board.checkBoard(x + 1, y))) // close to a wall in the left + a shape in the right
//			
//			return false;
//	}
//	return true;
//}

bool Shape::canTheShapeRotate(const TetrisBoard& board) {

	int centerY = shape[2].getY(), centerX = shape[2].getX();
	int x_new, y_new, x_old, y_old, center = centerX + centerY;

	for (int i = 0; i < SIZE; i++) {
		x_old = shape[i].getX();
		y_old = shape[i].getY();
		x_new = center - y_old;
		y_new = centerY - centerX + x_old;
		if (board.getCoord(x_new, y_new) || x_new >= COLUMNS || y_new >= ROWS + Board_Gap || x_new <= 1)
			return false;
	}
	return true;
}


int Shape::move(int direction, TetrisBoard& board) {
	int degree = getDegree();
	int x, y, check = 1;

	if (!(board.checkPos(this, direction) == TetrisBoard::FREE_SPACE))
		return TetrisBoard::MOVE_FAIL;


	for (int j = 0; j < SIZE; j++)
		shape[j].draw(BLANK_SPACE);

	if (direction != UP) { // the shape won't rotate
		for (int j = 0; j < SIZE; j++)
			shape[j].move(direction);
	}
	else {

		check = canTheShapeRotate(board);

		//if (check) {
		//	if (degree == DEG_0 || degree == DEG_180) //faces down
		//	{
		//		for (int j = 0; j < SIZE; j++) {
		//			if (shape[j].getY() == ROWS+1 || board.checkBoard(shape[j].getX(), shape[j].getY() + 1)
		//				|| board.checkBoard(shape[j].getX(), shape[j].getY() + 2))
		//			{
		//				for (int i = 0; i < SIZE; i++) {
		//					y = shape[i].getY();
		//					shape[i].setY(y - 2);
		//				}
		//				break;
		//			}
		//		}
		//	}
		//	else // checking right/left 
		//	{
		//		for (int j = 0; j < SIZE; j++) {
		//			if (shape[j].getX() <= 2 || board.checkBoard(shape[j].getX() - 1, shape[j].getY())
		//				|| board.checkBoard(shape[j].getX() - 2, shape[j].getY()))
		//			{
		//				for (int i = 0; i < SIZE; i++) {
		//					x = shape[i].getX();
		//					shape[i].setX(x + 1);
		//				}
		//				break;
		//			}
		//			if (shape[j].getX() >= COLUMNS-1 || board.checkBoard(shape[j].getX() + 1, shape[j].getY())
		//				|| board.checkBoard(shape[j].getX() + 2, shape[j].getY()))
		//			{
		//				for (int i = 0; i < SIZE; i++) {
		//					x = shape[i].getX();
		//					if (degree == DEG_90)
		//						shape[i].setX(x - 1);
		//					else
		//						shape[i].setX(x - 2);
		//				}
		//				break;
		//			}
		//		}
		//	}
		//}

		if (check)
			rotate(degree);

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
	
		if (theShapeNum == DEFAULT_OBJ_COLOR)
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
			return CYAN;
		case TEE:
			return LIGHTGREEN;
		case GUN:
			return LIGHTBLUE;
		default:
			return GREEN;
		}

}
