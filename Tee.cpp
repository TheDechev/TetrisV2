#include "Tee.h"
#include "TetrisBoard.h"

Tee::Tee()
{
	int k = 5;
	SIZE = 4;
	for (int i = 0; i < SIZE; i++) {

		shape[i].setX(k);
		if (i == 1) {
			shape[i].setY(Point::START_Y);
			continue;
		}
		shape[i].setY(Point::START_Y+1);
		k++;
	}
	setTextColor(whichColor(TEE));
	setShape(TEE);
}

void Tee::rotate(int Degree) {
	int x, y, k = -1;
	switch (Degree) {

	case DEG_0:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();

			shape[i].setX(x - k );
			if (i == 1)
				shape[i].setY(y - k);
			else
				shape[i].setY(y + k);
			if(i!=0)
				k++;
		}
		setDegree(DEG_90);

		break;

	case DEG_90:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if(i%2==0 || i==3)
				shape[i].setX(x - k);
			else
				shape[i].setX(x + k);
			
			shape[i].setY(y - k);
			if (i != 0)
				k++;
		}
		setDegree(DEG_180);

		break;

	case DEG_180:

		for (int  i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if (i % 2 == 0 || i==3)
				shape[i].setY(y - k);
			else
				shape[i].setY(y + k);


			shape[i].setX(x + k);
			if(i!=0)
				k++;
		}
		setDegree(DEG_270);

		break;

	case DEG_270:

		for (int i = 0; i < SIZE; i++) {
			x = shape[i].getX();
			y = shape[i].getY();
			if (i % 2 == 0 || i == 3)
				shape[i].setX(x + k);
			else
				shape[i].setX(x - k);


			shape[i].setY(y + k);
			if (i != 0)
				k++;
		}
		setDegree(DEG_0);

		break;
	}
}
