#ifndef _Zigzag_H
#define _Zigzag_H
#include <iostream>
#include "Shape.h"
using namespace std;

class Zigzag : public Shape {

public:

	Zigzag();
	void move(int direction, const TetrisBoard& board);
	void rotate(int Degree);
};

#endif