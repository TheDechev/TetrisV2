#ifndef _Line_H
#define _Line_H
#include <iostream>
#include "Shape.h"
using namespace std;

class TetrisBoard;		// Foward decleration for TetrisBoard	


class Line : public Shape {

public:
	int move(int direction,  TetrisBoard& board);
	Line();
	void rotate(int Degree);

};

#endif