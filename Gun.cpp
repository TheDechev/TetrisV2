#include "Gun.h"
#include "TetrisBoard.h"

Gun::Gun() {
	int k = 5;
	SIZE = 4;
	shape[0].setX(k);
	shape[1].setX(k);
	shape[0].setY(Point::START_Y);
	shape[1].setY(Point::START_Y + 1);
	for (int i = 2; i < SIZE; i++) {
		k++;
		shape[i].setX(k);
		shape[i].setY(Point::START_Y + 1);
	}
	setTextColor(whichColor(GUN));
	setShape(GUN);
}

void Gun::rotate(int Degree) {
	int x, y, k = -1;
	switch (Degree) {

	case DEG_0:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			shape[i].setX(x - k + 1);
			if (i != 0)
				shape[i].setY(y + k - 1);
			
			k++;
		}
			setDegree(DEG_90);

			break;

	case DEG_90:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if(i!=0)
				shape[i].setX(x - k + 1);
			shape[i].setY(y - k + 1);
			k++;
		}
		setDegree(DEG_180);

		break;

	case DEG_180:

		for (int i = SIZE-1; i >= 0; i--) {
			x = shape[i].getX();
			y = shape[i].getY();
			shape[i].setX(x - k);
			if(i!=0)
				shape[i].setY(y + k);
			k++;
		}
		setDegree(DEG_270);

		break;

	case DEG_270:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if(i!=0)
				shape[i].setX(x + k - 1);
			shape[i].setY(y + k - 1);
			k++;
		}
		setDegree(DEG_0);

		break;
	}
	
}


