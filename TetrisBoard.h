#ifndef _Board_H
#define _Board_H

#include "Shape.h"
#include "Config.h"

class TetrisBoard{
private:
	int Board[ROWS][COLUMNS], howManyDeleted;
public:
	enum { BOTTOM_ENCOUNTER = 11, SHAPE_ENCOUNTER = 12, FREE_SPACE, BOMB_EXPLODED, MOVED_SUCCESSFULLY, MOVE_FAIL, STOP_JOKER };
	
	TetrisBoard() { setBoard(); howManyDeleted = 0; }

	void printBoard(int currentY, const Shape* current);

	void setBoard();

	void updateBoard(Shape* current);

	void setCoord(int _x, int _y, int val) { Board[_y - Board_Gap][_x - 1] = val; }
	
	int getCoord(int _x, int _y) const;

	bool checkEndGame();

	int checkPos(const Shape* current, int direction);

	bool checkBoard(int _x, int _y) const;

	bool checkLine(int currentY);

	int deleteLines(const Shape* current, int minY, int maxY);

	void sethowManyDeleted(int num) { howManyDeleted += num; }

	int getHowManyDeleted() { return howManyDeleted; }

};

#endif _Board_H