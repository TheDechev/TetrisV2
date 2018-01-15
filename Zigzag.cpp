#include "Zigzag.h"
#include "TetrisBoard.h"

Zigzag::Zigzag() {
	int k = 5;
	SIZE = 4;
	for (int i = 0; i < SIZE; i++) {

		shape[i].setX(k);

		if(i<2)
			shape[i].setY(Point::START_Y);
		else
			shape[i].setY(Point::START_Y+1);
		if(i!=1)
			k++;
	}
	setTextColor(whichColor(ZIGZAG));
	setShape(ZIGZAG);
}


void Zigzag::rotate(int Degree) {
	int x, y, k = -1;
	switch (Degree) {

	case DEG_0:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if (i == 2) { continue;  }
			else if (i < 2) {
				shape[i].setX(x - k + 1);
				shape[i].setY(y + i);
			}
			else 
			{
				shape[i].setX(x - k);
				shape[i].setY(y + k);
			}
			k++;
		}
		setDegree(DEG_90);

		break;

	case DEG_90:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if (i == 2) { continue; }
			else if (i != 3){
				shape[i].setX(x - k - 1);
				shape[i].setY(y - k + 1);
				k++;
			}
			else{
				shape[i].setX(x - 1);
				shape[i].setY(y - 1);
			}
		}
		setDegree(DEG_180);

		break;

	case DEG_180:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if (i == 2) { continue; }
			else if (i != 3) {
				shape[i].setX(x + k - 1);
				shape[i].setY(y - k - 1);
				k++;
			}
			else{
				shape[i].setX(x + 1);
				shape[i].setY(y - 1);
			}
		}
		setDegree(DEG_270);

		break;

	case DEG_270:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if (i == 2) { continue; }
			else if (i != 3) {
				shape[i].setX(x + k + 1);
				shape[i].setY(y + k - 1);
				k++;
			}
			else {
				shape[i].setX(x + 1);
				shape[i].setY(y + 1);
			}
		}
		setDegree(DEG_0);

		break;
	}
}