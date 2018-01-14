#ifndef _Shape_H
#define _Shape_H
#include "Point.h"
#include "Config.h"
#include "GoToXY.h"
class TetrisBoard;		// Foward decleration for TetrisBoard	

class Shape{
private:
	
	int shapeType;	// Current shape type
	int Degree;		// Current
	char texture;		// Shape texture to print 
public:
	enum{START_X = 6, START_Y = 2};
	enum {DEG_0,DEG_90,DEG_180,DEG_270};
	enum { CUBE = 10, LINE ,ZIGZAG, GUN, TEE, JOKER, BOMB};
	enum{ DOWN, LEFT, UP, RIGHT, DEFAULT_SIZE, };
	Point shape[DEFAULT_SIZE];
	int SIZE;

	Shape(){
		setDegree(DEG_0);
		setTexture('%');
	}

	virtual int move(int direction,  TetrisBoard& board);
	virtual void rotate(int Degree) { }
	void getMinMaxShape(int& minY, int& maxY);

	Color whichColor(int theShapeNum=9999) const;

	bool canTheShapeRotate(const TetrisBoard& board);

	void setDegree(int pos) {
		Degree = pos;
	}

	int getDegree() {
		return Degree;
	}

	int getShape()const {
		return shapeType;
	}

	void setShape(int whichShape) {
		shapeType = whichShape;
	}

	void setTexture(char ch) {
		this->texture = ch;
	}

	char getTexture() {
		return texture;
	}
};

#endif _Shape_H