#ifndef _Gun_H
#define _Gun_H
#include "Shape.h"

class Gun : public Shape {
	
public:
	Gun();
	void rotate(int Degree);
};

#endif