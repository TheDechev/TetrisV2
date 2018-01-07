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

	enum {DEG_0,DEG_90,DEG_180,DEG_270};
	enum { DOWN, LEFT, UP, RIGHT, DEFAULT_SIZE, CUBE = 10, LINE , JOKER , BOMB ,ZIGZAG, GUN, TEE};
	Point shape[DEFAULT_SIZE];
	int SIZE;

	Shape(){
		setDegree(DEG_0);
		setTexture('%');
	}
	void setDegree(int pos) {
		Degree = pos;
	}
	int getDegree() {
		return Degree;
	}
	int getShape() const {
		return shapeType;
	}
	void setShape(int whichShape) {
		shapeType = whichShape;
	}
	void createNewShape(int whichShape);

	//void deleteShape() {
	//	if (getShape() == BOMB){
	//		gotoxy(shape[0].getX(), shape[0].getY());
	//		cout << " ";
	//	}
	//	delete[] shape;
	//}
	virtual void move(int direction, const TetrisBoard& board);
	virtual void rotate(int Degree) { }

	void setTexture(char ch){
		this->texture = ch;
	}

	char getTexture(){
		return texture;
	}

	void getMinMaxShape(int& minY, int& maxY);
	

	bool checkBomb(int direction, TetrisBoard& board, int& howManyBombed);
	int activateBomb(int x, int y, TetrisBoard& board);

	Color whichColor(int theShapeNum=9999) const;

	bool canTheShapeRotate(const TetrisBoard& board);
};

#endif _Shape_H