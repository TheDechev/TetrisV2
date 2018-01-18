#ifndef _Point
#define _Point
#include <iostream>
using namespace std;
#define _SHAPE_STOP -1

class Point{
	enum {DOWN,LEFT,UP,RIGHT};
	int x;
	int y;
public:
	enum { START_X = 6, START_Y = 2 };
	Point(){ // sets values to the top middle of the board
		this->x = START_X;
		this->y = START_Y;
	}
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
	void setPoint(int x, int y){
		this->x = x;
		this->y = y;
	}
	int getX() const {
		return this->x;
	}
	int getY() const {
		return this->y;
	}
	void setY(int y){
		this->y = y;
	}
	void setX(int x){
		this->x = x;
	}
	void draw(char ch);
	void move(int direction);
};


#endif