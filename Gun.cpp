#include "Gun.h"
#include "TetrisBoard.h"

Gun::Gun() {
	int k = 5;
	SIZE = 4;
	shape[0].setX(k);
	shape[1].setX(k);
	shape[0].setY(2);
	shape[1].setY(3);
	for (int i = 2; i < SIZE; i++) {
		k++;
		shape[i].setX(k);
		shape[i].setY(3);
	}
	setTextColor(whichColor(GUN));
	setShape(GUN);
}

void Gun::move(int direction, const TetrisBoard& board) {
	int degree = getDegree();
	int x, y, check = 1;

	for (int j = 0; j < SIZE; j++)
		shape[j].draw(' ');

	if (direction != UP) { // the shape won't rotate
		for (int j = 0; j < SIZE; j++)
			shape[j].move(direction);
	}
	else {

		check = canTheShapeRotate(board);

		if (check) {
			if (degree == DEG_0 || degree == DEG_180) //faces down
			{
				for (int j = 0; j < SIZE; j++) {
					if (shape[j].getY() == 16 || board.checkBoard(shape[j].getX(), shape[j].getY() + 1)
						|| board.checkBoard(shape[j].getX(), shape[j].getY() + 2))
					{
						for (int i = 0; i < SIZE; i++) {
							y = shape[i].getY();
							shape[i].setY(y - 2);
						}
						break;
					}
				}
			}
			else // checking right/left 
			{
				for (int j = 0; j < SIZE; j++) {
					if (shape[j].getX() <= 2 || board.checkBoard(shape[j].getX() - 1, shape[j].getY())
						|| board.checkBoard(shape[j].getX() - 2, shape[j].getY()))
					{
						for (int i = 0; i < SIZE; i++) {
							x = shape[i].getX();
							shape[i].setX(x + 1);
						}
						break;
					}
					if (shape[j].getX() >= 9 || board.checkBoard(shape[j].getX() + 1, shape[j].getY())
						|| board.checkBoard(shape[j].getX() + 2, shape[j].getY()))
					{
						for (int i = 0; i < SIZE; i++) {
							x = shape[i].getX();
							if (degree == DEG_90)
								shape[i].setX(x - 1);
							else
								shape[i].setX(x - 2);
						}
						break;
					}
				}
			}
		}

		if (check)
			rotate(degree);

	}

	setTextColor(whichColor());
	for (int j = 0; j < SIZE; j++)
		shape[j].draw(getTexture());
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


