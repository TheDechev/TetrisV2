#ifndef _Tee_H
#define _Tee_H
#include <iostream>
#include "Shape.h"
using namespace std;

class Tee : public Shape {

public:

	Tee();
	void move(int direction, const TetrisBoard& board);
	void rotate(int Degree);
};

#endif