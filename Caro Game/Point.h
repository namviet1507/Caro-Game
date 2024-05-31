#pragma once
#include "Struct.h"
#include "Controller.h"
#include "Game.h"


struct Point {
	int col = 0;
	int row = 0;
	char sign = ' ';

	void setRowCol(int, int);

	int getX();
	int getY();
};