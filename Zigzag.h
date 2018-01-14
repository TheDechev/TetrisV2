#ifndef _Zigzag_H
#define _Zigzag_H
#include <iostream>
#include "Shape.h"
using namespace std;

class Zigzag : public Shape {

public:

	Zigzag();
	int move(int direction,  TetrisBoard& board);
	void rotate(int Degree);

};

#endif