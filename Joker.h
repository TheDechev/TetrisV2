#ifndef _Joker_H
#define _Joker_H
#include "Shape.h"

class TetrisBoard;

class Joker : public Shape {

public:
	Joker();
	int move(int direction, TetrisBoard& board) override;
};

#endif