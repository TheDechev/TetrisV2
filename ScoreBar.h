#ifndef _ScoreBar_H
#define _ScoreBar_H
#include "TetrisBoard.h"

class Score{
	int scoreValue, distance, linesDeleted, partsNum, speedCounter, howManyBombed;
	int maxValueY[COLUMNS];
public:
	enum { VERY_SLOW = -2, SLOW, NORMAL, HIGH, VERY_HIGH };		// Speed const

	Score();

	int getSpeed(){ return speedCounter; }

	int getHowManyBombed() { return howManyBombed; }
	void updateHowManyBombed(int num) { howManyBombed += num; };

	void increaseSpeed();

	void decreaseSpeed();

	void printSpeed();

	void setLinesDeleted(int howMany, const Shape* currentShape);

	void printParts();

	int getLinesDeleted() { return linesDeleted; }

	void setMax(int x, int max){ maxValueY[x - 1] = max; }
	
	int getMax(int x) { return maxValueY[x - 1]; }

	void setDistance(Shape* currentShape, int minYshape);

	int getDistance(){ return distance; }

	void updateScoreValue(int addition) { scoreValue += addition; };
	
	int getScoreValue() { return scoreValue; }

	// The function checks and updates the max array
	bool isLarger(int currentX, int maxY);

	void printScore();

};

#endif _Score_H