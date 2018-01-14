#ifndef _Gun_H
#define _Gun_H
#include <iostream>
#include "Shape.h"
using namespace std;

class Gun : public Shape {
	
public:
	Gun();
	int move(int direction,  TetrisBoard& board);
	void rotate(int Degree);

};

#endif