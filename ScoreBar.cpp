#include "ScoreBar.h"

Score::Score() {
	scoreValue = 0;
	linesDeleted = 0;
	partsNum = 0;
	speedCounter = 0;
	howManyBombed = 0;
	for (int i = 0; i < COLUMNS; i++)
		maxValueY[i] = ROWS + Board_Gap;
	
}

void Score::increaseSpeed()
{
	if (speedCounter == VERY_HIGH)
		return;
	speedCounter++;
}

void Score::decreaseSpeed()
{
	if (speedCounter == VERY_SLOW)
		return;
	speedCounter--;
}

void Score::printSpeed() {
	setTextColor(WHITE);
	gotoxy(18, 0);
	for (int i = 0; i < 9; i++)
		cout << " ";
	gotoxy(18, 0);
	switch (speedCounter) {
	case VERY_SLOW:
		cout << "Very Slow";
		break;
	case SLOW:
		cout << "Slow";
		break;
	case NORMAL:
		cout << "Normal";
		break;
	case HIGH:
		cout << "High";
		break;
	case VERY_HIGH:
		cout << "Very High";
		break;
	}
}

void Score::setLinesDeleted(int howMany, const Shape* currentShape) {

	switch (howMany) {
	case 0:
		linesDeleted = 0;
		break;
	case 1:
		if (currentShape->getShape() == Shape::JOKER)
			linesDeleted = 50;
		else
			linesDeleted = 100;
		break;
	case 2:
		linesDeleted = 300;
		break;
	case 3:
		linesDeleted = 500;
		break;
	default: // tetris
		linesDeleted = 800;
		break;
	}
}

void Score::printParts()
{
	setTextColor(WHITE);
	gotoxy(7, 0);
	for (int i = 0; i < 4; i++)
		cout << " ";
	gotoxy(7, 0);
	cout << partsNum++;

}

void Score::setDistance(Shape* currentShape, int minYshape) {
	
		int currentMax = ROWS + Board_Gap, currentX;
		for (int i = 0; i < currentShape->SIZE; i++) {
			currentX = currentShape->shape[i].getX();
			if (getMax(currentX)<currentMax)
				currentMax = getMax(currentX);
		}
		distance = currentMax - minYshape;
	
}

bool Score::isLarger(int currentX, int maxY)
{
	if (maxY < maxValueY[currentX - 1]) {
		setMax(currentX, maxY);
		return true;
	}
	return false;
}

void Score::printScore()
{
	setTextColor(LIGHTGREEN);
	gotoxy(35, 0);
	for (int i = 0; i < COLUMNS; i++)
		cout << BLANK_SPACE;
	gotoxy(35, 0);
	cout << getScoreValue();
}

