#ifndef _Line_H
#define _Line_H
#include "Shape.h"

class TetrisBoard;		// Foward decleration for TetrisBoard	

class Line : public Shape {

public:
	Line();
	void rotate(int Degree);
};

#endif