#include "Joker.h"
#include "TetrisBoard.h"

Joker::Joker()
{
	SIZE = 1;
	shape[0].setY(START_Y);
	shape[0].setX(START_X);
	setTextColor(whichColor(JOKER));
	setShape(JOKER);
}

int Joker::move(int direction, TetrisBoard & board)
{
	int degree = getDegree();
	int check = 1;


	if (!(board.checkPos(this, direction) == TetrisBoard::SHAPE_ENCOUNTER) &&  (!(board.checkPos(this, direction) == TetrisBoard::FREE_SPACE)))
		return TetrisBoard::MOVE_FAIL;

	//WHY???	
	//currentShape->shape[0].getY() > 18)



	for (int j = 0; j < SIZE; j++) {

		// if the shape is the Joker AND there is another shape there then print the joker in top of it 
		if (board.getCoord(shape[0].getX(), shape[0].getY())) {
			setTextColor(whichColor(board.getCoord(shape[j].getX(), shape[j].getY())));
			if (board.getCoord(shape[j].getX(), shape[j].getY()) == JOKER)
				shape[j].draw('X');
			else 	// print the previous shape 
				shape[j].draw('%');

		}
		else
			shape[j].draw(' ');
	}

	if (direction != UP) { // the shape won't rotate
		for (int j = 0; j < SIZE; j++)
			shape[j].move(direction);
	}

	setTextColor(whichColor());
	for (int j = 0; j < SIZE; j++)
		shape[j].draw(getTexture());

	return TetrisBoard::MOVED_SUCCESSFULLY;
}
