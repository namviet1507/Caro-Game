#include "Game.h"
#pragma comment(lib, "winmm.lib")

bool Menu::music_is_open;
bool Menu::sound_is_open;
bool Menu::isVie = true;
void Menu::SetColor(int background_color, int text_color) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = background_color * 16 + text_color;
	SetConsoleTextAttribute(h, color_code);
}

void Menu::printRectangle(int left, int top, int width, int height)
{
	Controller::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++) {
		putchar(196);
	}
	putchar(191);
	int i = 0;
	for (; i < height; i++)
	{
		Controller::gotoXY(left, top + i + 1);
		putchar(179);
		Controller::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Controller::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void Menu::printMainScreen() {
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	system("cls");
	Game::isPlaying = false;
	if (Menu::music_is_open)
		Controller::playSound(BACKGROUND_SOUND);
	Menu::printLogo();
	int choice[5] = { 0,0,0,0,0 }, temp, key, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 14 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(52, 15);
				Menu::printVietnamese(L"CHƠI NGAY");
			}
			else {
				Controller::gotoXY(55, 15);
				cout << "PLAY";
			}
		}
		else {
			Controller::gotoXY(50, 15);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 14, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(52, 15);
			if (Menu::isVie) {
				Controller::gotoXY(52, 15);
				Menu::printVietnamese(L"CHƠI NGAY");
			}
			else {
				Controller::gotoXY(55, 15);
				cout << "PLAY";
			}
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 17 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 18);
				Menu::printVietnamese(L"CHƠI LẠI");
			}
			else {
				Controller::gotoXY(52, 18);
				cout << "LOAD GAME";
			}
		}
		else {
			Controller::gotoXY(50, 18);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 17, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 18);
			if (Menu::isVie) {
				Controller::gotoXY(53, 18);
				Menu::printVietnamese(L"CHƠI LẠI");
			}
			else {
				Controller::gotoXY(52, 18);
				cout << "LOAD GAME";
			}
		}

		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 20 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 21);
				Menu::printVietnamese(L"TRỢ GIÚP");
			}
			else {
				Controller::gotoXY(55, 21);
				cout << "HELP";
			}
		}
		else {
			Controller::gotoXY(50, 21);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 20, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 21);
			if (Menu::isVie) {
				Controller::gotoXY(53, 21);
				Menu::printVietnamese(L"TRỢ GIÚP");
			}
			else {
				Controller::gotoXY(55, 21);
				cout << "HELP";
			}
		}

		if (choice[3]) {
			Menu::SetColor(GREEN, BLUE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 23 + i);
				cout << "              ";
			}
			Controller::gotoXY(53, 24);
			if (Menu::isVie)
				Menu::printVietnamese(L"CÀI ĐẶT");
			else cout << "SETTING";
		}
		else {
			Controller::gotoXY(50, 24);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 23, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 24);
			if (Menu::isVie)
				Menu::printVietnamese(L"CÀI ĐẶT");
			else cout << "SETTING";
		}

		if (choice[4]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 26 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(54, 27);
				Menu::printVietnamese(L"THOÁT");
			}
			else {
				Controller::gotoXY(55, 27);
				cout << "EXIT";
			}
		}
		else {
			Controller::gotoXY(50, 27);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 26, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(54, 27);
			if (Menu::isVie) {
				Controller::gotoXY(54, 27);
				Menu::printVietnamese(L"THOÁT");
			}
			else {
				Controller::gotoXY(55, 27);
				cout << "EXIT";
			}
		}

		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					if (Menu::sound_is_open)
						Controller::playSound(ENTER_SOUND);
					system("cls");
					if (curChoice == 0) {
						Game::mode = Menu::printLevel();
						Game::signup();
						Game::setupGame();
					}
					else if (curChoice == 1) {
						Menu::readLoadGame();
					}
					else if (curChoice == 2) {
						Menu::helpScreen();
					}
					else if (curChoice == 3) {
						Menu::Setting();
					}
					else {
						Menu::SetColor(BLACK, BRIGHT_WHITE);
						system("cls");
						exit(0);
					}
				}
			}
			else {
				key = _getch();
				switch (key)
				{
				case KEY_UP:
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 4;
					break;
				case KEY_DOWN:
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice < 4) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
}

void Menu::printVietnamese(wstring text) {
	int mode = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << text;
	mode = _setmode(_fileno(stdout), _O_TEXT);
}

void Menu::Setting() {
	system("cls");
	system("color F0");
	int choice[4] = { 0,0,0,0 }, temp, key, curChoice = 0;
	Menu::SetColor(BRIGHT_WHITE, RED);
	cout << R"(

			  /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$ /$$   /$$  /$$$$$$ 
			 /$$__  $$| $$_____/|__  $$__/|__  $$__/|_  $$_/| $$$ | $$ /$$__  $$
			| $$  \__/| $$         | $$      | $$     | $$  | $$$$| $$| $$  \__/
			|  $$$$$$ | $$$$$      | $$      | $$     | $$  | $$ $$ $$| $$ /$$$$
			 \____  $$| $$__/      | $$      | $$     | $$  | $$  $$$$| $$|_  $$
			 /$$  \ $$| $$         | $$      | $$     | $$  | $$\  $$$| $$  \ $$
			|  $$$$$$/| $$$$$$$$   | $$      | $$    /$$$$$$| $$ \  $$|  $$$$$$/
			 \______/ |________/   |__/      |__/   |______/|__/  \__/ \______/ 
	)";
	Menu::SetColor(BRIGHT_WHITE, LIGHT_BLUE);
	fstream file;
	file.open("setting logo.txt", ios::in | ios::binary);
	string s;
	int line = 0;
	while (getline(file, s)) {
		Controller::gotoXY(2, 11 + line++);
		for (int i = 0; i < s.length(); i++) {
			if (isalpha(s[i]))
				putchar(219);
			else cout << " ";
		}
		cout << endl;
	}
	file.close();
	while (true) {
		choice[curChoice] = 1;
		if (Menu::music_is_open) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 12 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 13);
			if (Menu::isVie)
				Menu::printVietnamese(L"BẬT");
			else cout << "ON";
		}
		else {
			Menu::SetColor(RED, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 12 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 13);
			if (Menu::isVie)
				Menu::printVietnamese(L"TẮT");
			else cout << "OFF";
		}
		if (Menu::sound_is_open) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 15 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 16);
			if (Menu::isVie)
				Menu::printVietnamese(L"BẬT");
			else cout << "ON";
		}
		else {
			Menu::SetColor(RED, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 15 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 16);
			if (Menu::isVie)
				Menu::printVietnamese(L"TẮT");
			else cout << "OFF";
		}
		if (Menu::isVie) {
			Menu::SetColor(AQUA, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 18 + i);
				cout << "           ";
			}
			Controller::gotoXY(71, 19);
			Menu::printVietnamese(L"TIẾNG VIỆT");
		}
		else {
			Menu::SetColor(PURPLE, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 18 + i);
				cout << "           ";
			}
			Controller::gotoXY(72, 19);
			cout << "ENGLISH";
		}
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 12 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 13);
				Menu::printVietnamese(L"ÂM NHẠC");
			}
			else {
				Controller::gotoXY(54, 13);
				cout << "MUSIC";
			}
		}
		else {
			Controller::gotoXY(50, 13);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 12, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);

			if (Menu::isVie) {
				Controller::gotoXY(53, 13);
				Menu::printVietnamese(L"ÂM NHẠC");
			}
			else {
				Controller::gotoXY(54, 13);
				cout << "MUSIC";
			}
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 15 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 16);
				Menu::printVietnamese(L"ÂM THANH");
			}
			else {
				Controller::gotoXY(55, 16);
				cout << "SFX";
			}
		}
		else {
			Controller::gotoXY(50, 16);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 15, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			if (Menu::isVie) {
				Controller::gotoXY(53, 16);
				Menu::printVietnamese(L"ÂM THANH");
			}
			else {
				Controller::gotoXY(55, 16);
				cout << "SFX";
			}
		}

		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 18 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 19);
				Menu::printVietnamese(L"NGÔN NGỮ");
			}
			else {
				Controller::gotoXY(53, 19);
				cout << "LANGUAGE";
			}
		}
		else {
			Controller::gotoXY(50, 19);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 18, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			if (Menu::isVie) {
				Controller::gotoXY(53, 19);
				Menu::printVietnamese(L"NGÔN NGỮ");
			}
			else {
				Controller::gotoXY(53, 19);
				cout << "LANGUAGE";
			}
		}

		if (choice[3]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 21 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 22);
				Menu::printVietnamese(L"QUAY LẠI");
			}
			else {
				Controller::gotoXY(55, 22);
				cout << "BACK";
			}
		}
		else {
			Controller::gotoXY(50, 22);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 21, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			if (Menu::isVie) {
				Controller::gotoXY(53, 22);
				Menu::printVietnamese(L"QUAY LẠI");
			}
			else {
				Controller::gotoXY(55, 22);
				cout << "BACK";
			}
		}
		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					if (Menu::sound_is_open)
						Controller::playSound(ENTER_SOUND);
					if (curChoice == 0)
						Menu::music_is_open = !Menu::music_is_open;
					else if (curChoice == 1)
						Menu::sound_is_open = !Menu::sound_is_open;
					else if (curChoice == 2)
						Menu::isVie = !Menu::isVie;
					else
						if (Game::isPlaying) {
							stack<Point*> temp = Game::history;
							while (!temp.empty()) {
								Game::board[temp.top()->row][temp.top()->col].sign = temp.top()->sign;
								temp.pop();
							}
							system("color F0");
							system("cls");
							Game::printBoard();
							Game::printScoreBoard();
							Game::controlPoint();
						}
						else Menu::goBack();
				}
			}
			else {
				key = _getch();
				switch (key)
				{
				case KEY_UP:
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 3;
					break;
				case KEY_DOWN:
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice < 3) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
}

void Menu::printLogoEffect() {
	int cnt = 15;
	while (cnt--) {
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		Controller::gotoXY(15, 5);
		cout << " ________  ________  ________  ________          ________  ________  _____ ______   _______      " << endl;
		Controller::gotoXY(15, 6);
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		cout << "|\\   ____\\|\\   __  \\|\\   __  \\|\\   __  \\        |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     " << endl;
		Controller::gotoXY(15, 7);
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		cout << "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\       \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    " << endl;
		Controller::gotoXY(15, 8);
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		cout << " \\ \\  \\    \\ \\   __  \\ \\   _  _\\ \\  \\\\\\  \\       \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  " << endl;
		Controller::gotoXY(15, 9);
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		cout << "  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\\\\\  \\       \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ " << endl;
		Controller::gotoXY(15, 10);
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		cout << "   \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\" << endl;
		Controller::gotoXY(15, 11);
		Menu::SetColor(BRIGHT_WHITE, rand() % 6);
		cout << "    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|" << endl;
		Controller::gotoXY(5, 15);
		cout << R"(
			$$\   $$\                                                  $$$$$$\  
			$$ |  $$ |                                                $$  __$$\ 
			\$$\ $$  |                                                $$ /  $$ |
			 \$$$$  /                                                 $$ |  $$ |
			 $$  $$<                                                  $$ |  $$ |
			$$  /\$$\                                                 $$ |  $$ |
			$$ /  $$ |                                                 $$$$$$  |
			\__|  \__|                                                 \______/ 
	)";
		Sleep(125);
	}
}

void Menu::printLogoStandard() {
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(15, 5);
	cout << " ________  ________  ________  ________          ________  ________  _____ ______   _______      " << endl;
	Controller::gotoXY(15, 6);
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	cout << "|\\   ____\\|\\   __  \\|\\   __  \\|\\   __  \\        |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     " << endl;
	Controller::gotoXY(15, 7);
	Menu::SetColor(BRIGHT_WHITE, YELLOW);
	cout << "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\       \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    " << endl;
	Controller::gotoXY(15, 8);
	Menu::SetColor(BRIGHT_WHITE, YELLOW);
	cout << " \\ \\  \\    \\ \\   __  \\ \\   _  _\\ \\  \\\\\\  \\       \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  " << endl;
	Controller::gotoXY(15, 9);
	Menu::SetColor(BRIGHT_WHITE, RED);
	cout << "  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\\\  \\\\ \\  \\\\\\  \\       \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ " << endl;
	Controller::gotoXY(15, 10);
	Menu::SetColor(BRIGHT_WHITE, RED);
	cout << "   \\ \\_______\\ \\__\\ \\__\\ \\__\\\\ _\\\\ \\_______\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\" << endl;
	Controller::gotoXY(15, 11);
	Menu::SetColor(BRIGHT_WHITE, LIGHT_RED);
	cout << "    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|" << endl;
}

int check = 1;
void Menu::printLogo() {
	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(35, 2);
	if (Menu::isVie)
		Menu::printVietnamese(L"Bùi Nam Việt - Trương Quang Huy - Trương Hoàng Lâm");
	else cout << "Bui Nam Viet - Truong Quang Huy - Truong Hoang Lam";
	Controller::gotoXY(45, 3);
	cout << "23127516 - 23127530 - 23127402" << endl;
	if (check) {
		check = 0;
		Menu::printLogoEffect();
	}
	Menu::printLogoStandard();
	Controller::gotoXY(5, 15);
	Menu::SetColor(BRIGHT_WHITE, BLUE);
	cout << R"(
			$$\   $$\                                                  $$$$$$\  
			$$ |  $$ |                                                $$  __$$\ 
			\$$\ $$  |                                                $$ /  $$ |
			 \$$$$  /                                                 $$ |  $$ |
			 $$  $$<                                                  $$ |  $$ |
			$$  /\$$\                                                 $$ |  $$ |
			$$ /  $$ |                                                 $$$$$$  |
			\__|  \__|                                                 \______/ 
	)";
}

void Menu::helpScreen() {
	Controller::showCursor(false);
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	system("cls");
	int left = 5, top = 2, width = 92, height = 23;
	int line1 = 12, line2 = 19, line3 = 23;
	Menu::printRectangle(left, top, width, height);
	Controller::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line3);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		Controller::gotoXY(line2 + 1, top + i);
		putchar(179);
	}
	Controller::gotoXY(line2 + 1, line1);
	putchar(197);
	Controller::gotoXY(line2 + 1, line2);
	putchar(197);

	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 5);
	Menu::printVietnamese(L"Di chuyển:");
	Controller::gotoXY(left + 20, top + 1);
	Menu::printVietnamese(L"Người chơi 1: ");
	Controller::gotoXY(left + 22, top + 3);
	putchar(249);
	Menu::printVietnamese(L"'W' : Đi lên");
	Controller::gotoXY(left + 22, top + 5);
	putchar(249);
	Menu::printVietnamese(L"'S' : Đi xuống");
	Controller::gotoXY(left + 22, top + 7);
	putchar(249);
	Menu::printVietnamese(L"'A' : Sang trái");
	Controller::gotoXY(left + 22, top + 9);
	putchar(249);
	Menu::printVietnamese(L"'D' : Sang phải");
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left + 48, top + 1);
	Menu::printVietnamese(L"Người chơi 2: ");
	Controller::gotoXY(left + 50, top + 3);
	putchar(249);
	Menu::printVietnamese(L"'PgUp' : Đi lên");
	Controller::gotoXY(left + 50, top + 5);
	putchar(249);
	Menu::printVietnamese(L"'PgDn' : Đi xuống");
	Controller::gotoXY(left + 50, top + 7);
	putchar(249);
	Menu::printVietnamese(L"'Home' : Sang trái");
	Controller::gotoXY(left + 50, top + 9);
	putchar(249);
	Menu::printVietnamese(L"'End' : Sang phải");
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left + 75, top + 3);
	putchar(249);
	Menu::printVietnamese(L"'U' : Hoàn tác");
	Controller::gotoXY(left + 75, top + 5);
	putchar(249);
	Menu::printVietnamese(L"'L' : Lưu Game");
	Controller::gotoXY(left + 75, top + 7);
	putchar(249);
	Menu::printVietnamese(L"'Esc' : Thoát");
	Controller::gotoXY(left + 75, top + 9);
	putchar(249);
	Menu::printVietnamese(L"'Enter': Chọn");

	Menu::SetColor(BRIGHT_WHITE, LIGHT_RED);
	Controller::gotoXY(left + 3, top + 14);
	Menu::printVietnamese(L"Luật chơi:");
	Controller::gotoXY(left + 17, top + 11);
	int left1 = left + 17;
	putchar(249);
	Menu::printVietnamese(L" Bàn cờ caro có kích thước 14x14.");
	Controller::gotoXY(left1, top + 12);
	putchar(249);
	Menu::printVietnamese(L" Người chơi luân phiên đánh dấu con cờ X hoặc O của mình vào các ô trống.");
	Controller::gotoXY(left1, top + 13);
	putchar(249);
	Menu::printVietnamese(L" Người chơi chiến thắng là người đầu tiên đánh dấu đủ 5 ô X hoặc O");
	Controller::gotoXY(left1, top + 14);
	Menu::printVietnamese(L"  liên tiếp theo chiều ngang, chiều dọc hoặc đường chéo. ");
	Controller::gotoXY(left1, top + 15);
	putchar(249);
	Menu::printVietnamese(L" Nếu bảng hoàn toàn được lắp đầy và không một ai có thể tạo 5 ô liên tiếp");
	Controller::gotoXY(left1, top + 16);
	Menu::printVietnamese(L"  thì kết quả sẽ HÒA");

	Menu::SetColor(BRIGHT_WHITE, AQUA);
	Controller::gotoXY(left + 3, top + 19);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 18);
	Menu::printVietnamese(L"Dev 1: Bùi Nam Việt (23127516)");
	Controller::gotoXY(left + 31, top + 19);
	Menu::printVietnamese(L"Dev 2: Trương Hoàng Lâm (23127402)");
	Controller::gotoXY(left + 31, top + 20);
	Menu::printVietnamese(L"Dev 3: Trương Quang Huy (23127530)");

	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 22);
	Menu::printVietnamese(L"Giảng viên: ");
	Controller::gotoXY(left + 40, top + 22);
	Menu::printVietnamese(L"Trương Toàn Thịnh");

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175);
	Controller::gotoXY(47, 28);
	Menu::printVietnamese(L"Trở về");
	Controller::gotoXY(56, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6)
	{
		if (Menu::sound_is_open)
			Controller::playSound(ERROR_SOUND);
	}
	if (Menu::sound_is_open)
		Controller::playSound(ENTER_SOUND);
	if (Game::isPlaying) {
		stack<Point*> temp = Game::history;
		while (!temp.empty()) {
			Game::board[temp.top()->row][temp.top()->col].sign = temp.top()->sign;
			temp.pop();
		}
		system("color F0");
		system("cls");
		Game::printBoard();
		Game::printScoreBoard();
		Game::controlPoint();
	}
	else Menu::goBack();
}

int Menu::printLevel() {
	system("cls");
	Menu::printLogo();
	int choice[3] = { 0,0,0 }, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 17 + i);
				cout << "              ";
			}
			Controller::gotoXY(53, 18);
			if (Menu::isVie)
				Menu::printVietnamese(L"1 NGƯỜI");
			else cout << "1 PLAYER";
		}
		else {
			Controller::gotoXY(50, 18);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 17, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 18);
			if (Menu::isVie)
				Menu::printVietnamese(L"1 NGƯỜI");
			else cout << "1 PLAYER";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 21 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 22);
				Menu::printVietnamese(L"2 NGƯỜI");
			}
			else {
				Controller::gotoXY(52, 22);
				cout << "2 PLAYERS";
			}
		}
		else {
			Controller::gotoXY(50, 22);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 21, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			if (Menu::isVie) {
				Controller::gotoXY(53, 22);
				Menu::printVietnamese(L"2 NGƯỜI");
			}
			else {
				Controller::gotoXY(52, 22);
				cout << "2 PLAYERS";
			}
		}
		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 25 + i);
				cout << "              ";
			}
			if (Menu::isVie) {
				Controller::gotoXY(53, 26);
				Menu::printVietnamese(L"QUAY LẠI");
			}
			else {
				Controller::gotoXY(55, 26);
				cout << "BACK";
			}
		}
		else {
			Controller::gotoXY(50, 26);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 25, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);

			if (Menu::isVie) {
				Controller::gotoXY(53, 26);
				Menu::printVietnamese(L"QUAY LẠI");
			}
			else {
				Controller::gotoXY(55, 26);
				cout << "BACK";
			}
		}

		int temp, key;
		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					if (Menu::sound_is_open)
						Controller::playSound(ENTER_SOUND);
					return curChoice;
				}
			}
			else {
				key = _getch();
				if (Menu::sound_is_open)
					Controller::playSound(MOVE_SOUND);
				switch (key)
				{
				case KEY_UP:
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 2;
					break;
				case KEY_DOWN:
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					choice[curChoice] = 0;
					if (curChoice < 2) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
}

void Menu::goBack() {
	Menu::printMainScreen();
}

void Menu::readLoadGame() {
	Menu::SetColor(BRIGHT_WHITE, PURPLE);
	system("cls");
	cout << R"(
		 /$$        /$$$$$$   /$$$$$$  /$$$$$$$         /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$
		| $$       /$$__  $$ /$$__  $$| $$__  $$       /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/
		| $$      | $$  \ $$| $$  \ $$| $$  \ $$      | $$  \__/| $$  \ $$| $$$$  /$$$$| $$      
		| $$      | $$  | $$| $$$$$$$$| $$  | $$      | $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   
		| $$      | $$  | $$| $$__  $$| $$  | $$      | $$|_  $$| $$__  $$| $$  $$$| $$| $$__/   
		| $$      | $$  | $$| $$  | $$| $$  | $$      | $$  \ $$| $$  | $$| $$\  $ | $$| $$      
		| $$$$$$$$|  $$$$$$/| $$  | $$| $$$$$$$/      |  $$$$$$/| $$  | $$| $$ \/  | $$| $$$$$$$$
		|________/ \______/ |__/  |__/|_______/        \______/ |__/  |__/|__/     |__/|________/
	)";

	string filename = getFile();
	if (filename != "") {
		Game::processLoadFile(filename);
		return;
	}
	else {
		Menu::goBack();
	}



	//while (Controller::getConsoleInput() != 6)
	//{
	//	if (Menu::sound_is_open)
	//		Controller::playSound(ERROR_SOUND);
	//}
	//if (Menu::sound_is_open)
	//	Controller::playSound(ENTER_SOUND);
	//Menu::goBack();
}

void Menu::printListFile(int start, int end, vector<string> arrFilename) {
	int y = 0;
	for (int i = start; i < arrFilename.size() && i <= end; i++) {
		Menu::SetColor(BRIGHT_WHITE, BLACK);
		Controller::gotoXY(40, 15 + y);
		y++;
		cout << i + 1 << ". " << arrFilename[i];
		size_t x = arrFilename[i].size();
		while (x < 30) {
			cout << ' ';
			x++;
		}
	}
}

string Menu::getFile() {
	fstream listFile;
	listFile.open(LIST_FILE, ios::in | ios::binary);

	if (!listFile) {
		Menu::SetColor(BLACK, BRIGHT_WHITE);
		system("cls");
		exit(0);
		return "";
	}

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(35, 12, 40, 14);
	Controller::gotoXY(49, 13);
	Menu::printVietnamese(L"Danh sách FILE");
	Controller::gotoXY(36, 14);
	for (int i = 0; i < 39; i++) {
		putchar(196);
	}

	char* filename = new char[100]; // ten file user luu
	vector<string> arrFilename;
	bool check = true;
	while (listFile.read((char*)filename, 100)) {
		check = false;
		arrFilename.push_back(filename);
	}

	int left = 0;
	size_t right = arrFilename.size() - 1;
	while (left < right) {
		swap(arrFilename[left], arrFilename[right]);
		left++;
		right--;
	}

	if (arrFilename.size() == 0) {
		Menu::SetColor(BRIGHT_WHITE, BLACK);
		printRectangle(51, 27, 8, 2);
		Menu::SetColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(49, 28);
		putchar(175);
		Controller::gotoXY(53, 28);
		if (Menu::isVie)
			Menu::printVietnamese(L"Trở về");
		else
			cout << "BACK";
		Controller::gotoXY(62, 28);
		putchar(174);
		int key = Controller::getConsoleInput();
		while (key != 6) {
			if (Menu::sound_is_open)
				Controller::playSound(ERROR_SOUND);
			key = Controller::getConsoleInput();
		}
		return "";
	}

	int index = 0;
	int top = 0;
	int bot = 10;
	int y = 0;
	bool isBack = false;
	printListFile(top, bot, arrFilename);
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	printRectangle(51, 27, 8, 2);
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(53, 28);
	if (Menu::isVie)
		Menu::printVietnamese(L"Trở về");
	else
		cout << "BACK";


	Menu::SetColor(GREEN, BLACK);
	Controller::gotoXY(38, 15 + index);
	cout << index + 1 << ". " << arrFilename[index];
	size_t x = arrFilename[index].size();
	while (x < 30) {
		cout << ' ';
		x++;
	}

	while (true) {
		if (_kbhit()) {
			switch (Controller::getConsoleInput()) {
			case 2: // UP
				if (isBack) {
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					Menu::SetColor(BRIGHT_WHITE, RED);
					Controller::gotoXY(49, 28);
					putchar(32);
					Controller::gotoXY(62, 28);
					putchar(32);

					isBack = false;

					Menu::SetColor(GREEN, BLACK);
					Controller::gotoXY(38, 15 + y);
					cout << index + 1 << ". " << arrFilename[index];
					x = arrFilename[index].size();
					while (x < 30) {
						cout << ' ';
						x++;
					}
				}
				else if (index > 0) {
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					Menu::SetColor(BRIGHT_WHITE, BLACK);
					Controller::gotoXY(38, 15 + y);
					cout << "  " << index + 1 << ". " << arrFilename[index];
					size_t x = arrFilename[index].size();
					while (x < 30) {
						cout << ' ';
						x++;
					}

					if (index == top) {
						top--;
						bot--;
						printListFile(top, bot, arrFilename);
					}
					else y--;
					index--;

					Menu::SetColor(GREEN, BLACK);
					Controller::gotoXY(38, 15 + y);
					cout << index + 1 << ". " << arrFilename[index];
					x = arrFilename[index].size();
					while (x < 30) {
						cout << ' ';
						x++;
					}
				}
				else if (Menu::sound_is_open)
					Controller::playSound(ERROR_SOUND);
				break;
			case 5: // DOWN
				if (isBack) {
					if (Menu::sound_is_open)
						Controller::playSound(ERROR_SOUND);
				}
				else if (index < arrFilename.size() - 1) {
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);

					Menu::SetColor(BRIGHT_WHITE, BLACK);
					Controller::gotoXY(38, 15 + y);
					cout << "  " << index + 1 << ". " << arrFilename[index];
					size_t x = arrFilename[index].size();
					while (x < 30) {
						cout << ' ';
						x++;
					}

					if (index == bot) {
						top++;
						bot++;
						printListFile(top, bot, arrFilename);
					}
					else y++;
					index++;

					Menu::SetColor(GREEN, BLACK);
					Controller::gotoXY(38, 15 + y);
					cout << index + 1 << ". " << arrFilename[index];
					x = arrFilename[index].size();
					while (x < 30) {
						cout << ' ';
						x++;
					}
				}
				else if (index == arrFilename.size() - 1) {
					if (Menu::sound_is_open)
						Controller::playSound(MOVE_SOUND);
					isBack = true;

					Menu::SetColor(BRIGHT_WHITE, BLACK);
					Controller::gotoXY(38, 15 + y);
					cout << "  " << index + 1 << ". " << arrFilename[index];
					size_t x = arrFilename[index].size();
					while (x < 30) {
						cout << ' ';
						x++;
					}

					Menu::SetColor(BRIGHT_WHITE, BLACK);
					printRectangle(51, 27, 8, 2);
					Menu::SetColor(BRIGHT_WHITE, RED);
					Controller::gotoXY(49, 28);
					putchar(175);
					Controller::gotoXY(53, 28);
					if (Menu::isVie)
						Menu::printVietnamese(L"Trở về");
					else
						cout << "BACK";
					Controller::gotoXY(62, 28);
					putchar(174);
				}
				break;
			case 6: // Enter
				if (isBack) return "";
				else {
					strcpy_s(filename, 100, arrFilename[index].c_str());
					char* temp = new char[100];
					strcpy_s(temp, 100, filename);
					strcpy_s(Game::FILENAME, 100, filename);
					strcat_s(temp, 100, ".bin\0");
					return temp;
				}
				break;
			default:
				break;
			}
		}
	}
	return "";
}
