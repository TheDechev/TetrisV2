
#include "GoToXY.h"
#include "TetrisBoard.h"
#include "Cube.h"
#include "Line.h"

int Shape::canTheShapeRotate(const TetrisBoard& board) {

	int centerY = shape[2].getY(), centerX = shape[2].getX();
	int x_new, y_new, x_old, y_old, center = centerX + centerY;
	int left_flag = 0, shape_flag = 0, right_flag = 0;
	for (int i = 0; i < SIZE; i++) {
		x_old = shape[i].getX();
		y_old = shape[i].getY();
		x_new = center - y_old;
		y_new = centerY - centerX + x_old;
		//either a shape was encountered or a game wall
		if (board.getCoord(x_new, y_new) || y_new > ROWS + Board_Gap || y_new < Board_Gap - 1) shape_flag++;
		else if (x_new > COLUMNS) right_flag++;
		else if (x_new < 1) left_flag++;
	}
	//shapes encounter has higher priority than the walls 
	if (shape_flag) return CANT_OTHER;
	else if (right_flag) return CANT_RIGHT;
	else if (left_flag) return CANT_LEFT;
	else return CAN_MOVE;
	
}

int Shape::move(int direction, TetrisBoard& board) {
	int degree = getDegree();
	int x, check = 1;

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
		while (check == CANT_LEFT || check == CANT_RIGHT) {
			if (check == CANT_LEFT) {
				for (int i = 0; i < SIZE; i++) {
					x = shape[i].getX();
					shape[i].setX(x + 1);
				}
			}
			else if (check == CANT_RIGHT) {
				for (int i = 0; i < SIZE; i++) {
					x = shape[i].getX();
					shape[i].setX(x - 1);
				}
			}
			check = canTheShapeRotate(board);
		}

		if (check!=CANT_OTHER)
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
