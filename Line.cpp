#include "Line.h"
#include "TetrisBoard.h"

Line::Line() {
	int k = 1;
	SIZE = 4;
	for (int i = 0; i < SIZE; i++) {
		shape[i].setX(Point::START_X - 2 + i);
		shape[i].setY(Point::START_Y);
	}
	setTextColor(whichColor(LINE));
	setShape(LINE);
}

void Line::rotate(int Degree) {

	int centerY = shape[2].getY(), centerX = shape[2].getX();
	int x_new, y_new, x_old, y_old, center = centerX + centerY;

	for (int i = 0; i < SIZE; i++) {
		x_old = shape[i].getX();
		y_old = shape[i].getY();
		x_new = center - y_old;
		y_new = centerY - centerX + x_old;
		shape[i].setX(x_new);
		shape[i].setY(y_new);
	}

}

