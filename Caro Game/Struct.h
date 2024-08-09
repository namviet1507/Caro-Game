#pragma once
#include <iostream>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <codecvt>
#include <locale>
#include <string>
#include <windows.h>
#include <conio.h>
#include <random>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <map>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>

// COLOR CODE
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

// SOUNDTRACK
#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define MATCH_SOUND 3
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define LOSE_SOUND 6

// char
#define _DELETE ' '
#define LIST_FILE "listFile.bin"

using namespace std;

struct Player {
	wstring playerName;
	int score = 0;
};

struct Menu {
	static bool music_is_open;
	static bool sound_is_open;
	static bool isVie;
	static void printMainScreen();							//In ra màn hình chính
	static void printLogo();
	static void printLogoEffect();
	static void printLogoStandard();
	static void Setting();
	static void goBack();									//Trở về menu
	static void SetColor(int, int);							//Cài đặt màu
	static void readLoadGame();								//Đọc bảng xếp hạng
	static void printRectangle(int, int, int, int);			//Vẽ hình chữ nhật
	static int printLevel();								//In ra mức độ chơi
	static void helpScreen();								//Màn hình hướng dẫn
	static void printVietnamese(wstring);

	static void printListFile(int start, int end, vector<string> arrFilename);
	static string getFile();
};