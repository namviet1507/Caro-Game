#pragma once
#include "Struct.h"
#include "Controller.h"
#include "Point.h"
#include <vector>
#include <stack>

#define BOARD_SIZE 14
#define BOARD_LEFT 2
#define BOARD_TOP 0


struct Game {
	static Point** board;
	static Point* cur_point;
	static Point* bot_point;
	static stack<Point*> history;

	static int mode;
	static int wonp1;
	static int wonp2;
	static bool isPlayting;
	static bool XWin;

	static void setupGame();
	static void createBoard();
	static void printBoard();
	static void printScoreBoard();
	static void freeBoard();

	static void controlPoint();
	static void printPoint(Point* point, int background, int color);
	static void resetGame();
	static void processWinGame(int, Point* point);
	static void processBot();

	static void processSaveFile(char);
	static void processLoadFile(string filename);

	// nếu nhấn enter mới check
	static bool checkWinGameCol(Point*); // kiểm tra theo chiều dọc
	static bool checkWinGameRow(Point*); // kiểm tra theo chiều ngang
	static bool checkWinGameDM(Point*); // kiểm tra theo đường chéo (dấu sắc)
	static bool checkWinGameDS(Point*); // kiểm tra theo đường chéo (dấu huyền)
	static bool checkDraw();

};