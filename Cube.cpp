#include "Cube.h"
#include "Point.h"
#include "GoToXY.h"

Cube::Cube()
{
	setShape(CUBE);
	int k = 1;
	SIZE = 4;
	for (int i = 0; i < SIZE; i++) {
		if (i % 2 == 0) {
			shape[i].setX(Point::START_X - 1);
			shape[i].setY(k + 2);
		}
		else {
			shape[i].setX(Point::START_X);
			shape[i].setY(k + 2);
			k--;
		}
	}
	setTextColor(whichColor(CUBE));
	setShape(CUBE);
}
