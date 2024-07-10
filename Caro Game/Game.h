#pragma once
#include "Struct.h"
#include "Controller.h"
#include "Point.h"
#include <vector>
#include <stack>
#include <set>

#define BOARD_SIZE 14
#define BOARD_LEFT 2
#define BOARD_TOP 0

#define COLOR_X RED
#define COLOR_O BLUE 

struct Game {
	static Point** board;
	static Point* cur_point;
	static Point* bot_point;
	static stack<Point*> history;

	static int mode;				// Chế độ Game
	static char NAMEFILE[100];
	static char FILENAME[100];
	static bool isPlaying;			// check còn đang chơi không
	static bool XWin;				// check X win hay O win
	static bool isDraw;				// check có hòa không

	static void setupGame();		// Cài đặt game
	static void createBoard();		// Tạo bảng
	static void printBoard();		// In bảng
	static void printScoreBoard();	// In bảng điểm
	static void freeBoard();		// Xóa bảng
	static void signup();			// Đăng ký

	static void controlPoint();		// Điều khiển điểm
	static void printPoint(Point* point, int background, int color);	// In điểm
	static void resetGame();		// reset Game
	static void processWinGame(int, Point* point);
	static void processBot();

	static void getScore(int score[4][BOARD_SIZE][BOARD_SIZE], char sign);
	static void processBotHard();

	static void UndoStep(char& last_sign);	// Undo

	static void processSaveFile(char);		// Lưu file
	static void processLoadFile(string filename);	// Tải file

	// nếu nhấn enter mới check
	static bool checkWinGameCol(Point*); // kiểm tra theo chiều dọc
	static bool checkWinGameRow(Point*); // kiểm tra theo chiều ngang
	static bool checkWinGameDM(Point*); // kiểm tra theo đường chéo (dấu sắc)
	static bool checkWinGameDS(Point*); // kiểm tra theo đường chéo (dấu huyền)
	static bool checkDraw();

	static void countdown(char, time_t, int, bool&);	// Đếm ngược thời gian

};

