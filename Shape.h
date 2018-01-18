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
	enum { DEFAULT_OBJ_COLOR=999, DEFAULT_SIZE = 4};			
	enum { DEG_0,DEG_90,DEG_180,DEG_270};						// Shape's degree status consts
	enum { CUBE = 10, LINE ,ZIGZAG, GUN, TEE, JOKER, BOMB};		// Shape's names consts
	enum { DOWN, LEFT, UP, RIGHT };								
	Point shape[DEFAULT_SIZE];
	int SIZE;

	Shape(){
		setDegree(DEG_0);
		setTexture('%');
	}
	
	virtual int move(int direction,  TetrisBoard& board);

	virtual void rotate(int Degree) {}

	// The function is getting (by ref) the minimun and the maximum Y values
	// of the current shape
	void getMinMaxShape(int& minY, int& maxY);

	Color whichColor(int theShapeNum= DEFAULT_OBJ_COLOR) const;

	bool canTheShapeRotate(const TetrisBoard& board);

	void setDegree(int pos) { Degree = pos; }

	int getDegree() const { return Degree; }

	int getShape() const { return shapeType; }

	void setShape(int whichShape) { shapeType = whichShape; }

	void setTexture(char ch) { this->texture = ch; }

	char getTexture() const { return texture; }
};

#endif _Shape_H