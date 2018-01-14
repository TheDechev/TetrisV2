#ifndef _Joker_H
#define _Joker_H

#include <iostream>
#include "Shape.h"

using namespace std;

class TetrisBoard;

class Joker : public Shape {
public:
	Joker();
	int move(int direction, TetrisBoard& board);

};

#endif