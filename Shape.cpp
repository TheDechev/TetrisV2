
#include "GoToXY.h"
#include "TetrisBoard.h"
#include "Cube.h"
#include "Line.h"


//void Shape::createShape(int whichShape) {
//	int k=1;
//	switch (whichShape) {
//	
//
//
//	//case JOKER:
//	//	shape = new Point;
//	//	shape->setX(6);
//	//	shape->setY(2);
//	//	setTexture('X');
//	//	SIZE = 1;
//	//	break;
//	//case BOMB:
//	//	shape = new Point;
//	//	shape->setX(6);
//	//	shape->setY(2);
//	//	setTexture('@');
//	//	SIZE = 1;
//	//	break;
//	}
//	setTextColor(whichColor(whichShape));
//	setShape(whichShape);
//	setDegree(DEG_0);
//}

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



void Shape::move(int direction,const TetrisBoard& board) {
	
	int degree = getDegree();
	int check = 1;

	for (int j = 0; j < SIZE; j++)
		shape[j].draw(' ');

	if (direction != UP) { // the shape won't rotate
		for (int j = 0; j < SIZE; j++)
			shape[j].move(direction);
	}

	setTextColor(whichColor());
	for (int j = 0; j < SIZE; j++)
		shape[j].draw(getTexture());

	
}

bool Shape::checkBomb(int direction, TetrisBoard& board, int& howManyBombed){
	int x= shape[0].getX(), y=shape[0].getY();

	shape[0].draw(getTexture());

	// checks if the bomb can explode in the direction entered
	if ((direction == LEFT && board.checkBoard(x - 1, y) == true) ||
		(direction == RIGHT && board.checkBoard(x + 1, y) == true) ||
		(board.checkBoard(x, y + 1) == true) || y>=Board_Gap+ROWS-1)
	{
		howManyBombed = activateBomb(x, y, board); // update the pieces that have been blown
		return true;
	}


	gotoxy(x, y);
	return false;


}

int Shape::activateBomb(int x, int y, TetrisBoard& board){
	int tempX, tempY = y - 1 , howManyBombed = 0;
	for (int i = 0; i < 3; i++){

		tempX = x - 1;
		for (int j = 0; j < 3; j++){
			// if it's within the board limits and a shape has been met, update the counter (howManyBombed)
			if (tempX > 0 && tempX <= COLUMNS && tempY > Board_Gap && tempY < ROWS+Board_Gap){
				if (board.getCoord(tempX, tempY))
					howManyBombed++;

				// explosion effect
				if (j%2==0)
					setTextColor(YELLOW);
				else
					setTextColor(RED);
				gotoxy(tempX, tempY);
				cout << "*";
				Sleep(50);
				
				gotoxy(tempX, tempY);
				cout << " ";
				board.setCoord(tempX, tempY,0);
			}
			tempX++;
		}
		tempY++;

	}
	return howManyBombed;
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
