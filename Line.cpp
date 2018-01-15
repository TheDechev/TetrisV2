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

	int x, y, k = -1;
	switch (Degree) {

	case DEG_0:
		// the switch case is future proof
		switch (getShape())
		{

		case LINE:
			for (int i = 0; i < SIZE; i++) {
				x = shape[i].getX();
				y = shape[i].getY();
				shape[i].setX(x - k + 1);
				shape[i].setY(y + k);
				k++;
			}
			setDegree(DEG_90);
		}
		break;

	case DEG_90:

		switch (getShape())
		{

		case LINE:
			for (int i = 0; i < SIZE; i++) {
				x = shape[i].getX();
				y = shape[i].getY();
				shape[i].setX(x - k);
				shape[i].setY(y - k + 1);
				k++;
			}
			setDegree(DEG_180);
		}
		break;

	case DEG_180:

		switch (getShape())
		{
		case LINE:
			for (int i = 0; i < SIZE; i++) {
				x = shape[i].getX();
				y = shape[i].getY();
				shape[i].setX(x + k - 1);
				shape[i].setY(y - k);
				k++;
			}
			setDegree(DEG_270);
		}
		break;

	case DEG_270:

		switch (getShape())
		{
		case LINE:
			for (int i = 0; i < SIZE; i++) {
				x = shape[i].getX();
				y = shape[i].getY();
				shape[i].setX(x + k);
				shape[i].setY(y + k - 1);
				k++;
			}
			setDegree(DEG_0);
		}

		break;
	}

}

