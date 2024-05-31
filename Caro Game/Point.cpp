#include "Game.h"

void Point::setRowCol(int _row, int _col) {
	row = _row;
	col = _col;
}

int Point::getX() {
	return BOARD_LEFT + 4 * col + 1;
}

int Point::getY() {
	return BOARD_TOP + 2 * row + 1;
}