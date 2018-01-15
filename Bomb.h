#ifndef _Bomb_H
#define _Bomb_H
#include "Shape.h"

class TetrisBoard;

enum{ EXPLOSION_AREA = 3 };

class Bomb : public Shape  {
public:
	Bomb();
	bool checkBomb(int direction, TetrisBoard& board);
	int activateBomb(int x, int y, TetrisBoard& board);
	int move(int direction, TetrisBoard& board) override;
};

#endif