#ifndef _Cube_H
#define _Cube_H
#include <iostream>
#include "Shape.h"

using namespace std;

class Cube: public Shape{
	
public:
	Cube() {
		setShape(CUBE);
		int k = 1;
		SIZE = 4;
		for (int i = 0; i < SIZE; i++) {
			if (i % 2 == 0) {
				shape[i].setX(5);
				shape[i].setY(k + 2);
			}
			else {
				shape[i].setX(6);
				shape[i].setY(k + 2);
				k--;
			}
		}
		setTextColor(whichColor(CUBE));
		setShape(CUBE);
	};

};

#endif