#include "Joker.h"
#include "TetrisBoard.h"

Joker::Joker()
{
	SIZE = 1;
	shape[0].setY(Point::START_Y);
	shape[0].setX(Point::START_X);
	setTextColor(whichColor(JOKER));
	setShape(JOKER);
	setTexture('X');
	
}

int Joker::move(int direction, TetrisBoard & board)
{
	if (!(board.checkPos(this, direction) == TetrisBoard::SHAPE_ENCOUNTER) &&  (!(board.checkPos(this, direction) == TetrisBoard::FREE_SPACE)))
		return TetrisBoard::MOVE_FAIL;

	// if the shape is the Joker AND there is another shape there then print the joker in top of it 
	if (board.getCoord(shape[0].getX(), shape[0].getY())) {
		setTextColor(whichColor(board.getCoord(shape[0].getX(), shape[0].getY())));
		if (board.getCoord(shape[0].getX(), shape[0].getY()) == JOKER)
			shape[0].draw('X');
		else 	// print the previous shape 
			shape[0].draw('%');
	}
	else
		shape[0].draw(' ');
	

	if (direction != UP) { // the shape won't rotate
		shape[0].move(direction);
	}

	setTextColor(whichColor());
	shape[0].draw(getTexture());

	return TetrisBoard::MOVED_SUCCESSFULLY;
}
