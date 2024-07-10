#include "Struct.h"
#include "Controller.h"
#include "Game.h"
#include "Point.h"
#pragma comment(lib, "winmm.lib")

bool Menu::music_is_open;
bool Menu::sound_is_open;
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
			Controller::gotoXY(52, 15);
			Menu::printVietnamese(L"CHƠI NGAY");
		}
		else {
			Controller::gotoXY(50, 15);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 14, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(52, 15);
			Menu::printVietnamese(L"CHƠI NGAY");
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 17 + i);
				cout << "              ";
			}
			Controller::gotoXY(52, 18);

			cout << "LOAD GAME";
		}
		else {
			Controller::gotoXY(50, 18);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 17, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(52, 18);
			cout << "LOAD GAME";
		}

		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 20 + i);
				cout << "              ";
			}
			Controller::gotoXY(53, 21);
			Menu::printVietnamese(L"TRỢ GIÚP");
		}
		else {
			Controller::gotoXY(50, 21);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 20, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 21);
			Menu::printVietnamese(L"TRỢ GIÚP");
		}

		if (choice[3]) {
			Menu::SetColor(GREEN, BLUE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 23 + i);
				cout << "              ";
			}
			Controller::gotoXY(53, 24);
			Menu::printVietnamese(L"CÀI ĐẶT");
		}
		else {
			Controller::gotoXY(50, 24);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 23, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 24);
			Menu::printVietnamese(L"CÀI ĐẶT");
		}

		if (choice[4]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 26 + i);
				cout << "              ";
			}
			Controller::gotoXY(54, 27);
			Menu::printVietnamese(L"THOÁT");
		}
		else {
			Controller::gotoXY(50, 27);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 26, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(54, 27);
			Menu::printVietnamese(L"THOÁT");
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
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << text;
	_setmode(_fileno(stdout), _O_TEXT);
}

void Menu::Setting() {
	system("cls");
	system("color F0");
	int choice[3] = { 0,0,0 }, temp, key, curChoice = 0;
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
				Controller::gotoXY(70, 16 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 17);
			cout << "ON";
		}
		else {
			Menu::SetColor(RED, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 16 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 17);
			cout << "OFF";
		}
		if (Menu::sound_is_open) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 19 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 20);
			cout << "ON";
		}
		else {
			Menu::SetColor(RED, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(70, 19 + i);
				cout << "           ";
			}
			Controller::gotoXY(74, 20);
			cout << "OFF";
		}
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 16 + i);
				cout << "              ";
			}
			Controller::gotoXY(54, 17);
			cout << "MUSIC";
		}
		else {
			Controller::gotoXY(50, 17);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 16, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(54, 17);
			cout << "MUSIC";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 19 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 20);
			cout << "SFX";
		}
		else {
			Controller::gotoXY(50, 20);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 19, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(55, 20);
			cout << "SFX";
		}

		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_PURPLE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 22 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 23);
			cout << "BACK";
		}
		else {
			Controller::gotoXY(50, 23);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 22, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(55, 23);
			cout << "BACK";
		}

		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					if (Menu::sound_is_open)
						Controller::playSound(ENTER_SOUND);
					if (curChoice == 0) {
						if (Menu::music_is_open)
							Menu::music_is_open = false;
						else
							Menu::music_is_open = true;
					}
					else if (curChoice == 1) {
						if (Menu::sound_is_open)
							Menu::sound_is_open = false;
						else
							Menu::sound_is_open = true;
					}
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
	Menu::printVietnamese(L"Bùi Nam Việt - Trương Quang Huy - Trương Hoàng Lâm");
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
			cout << "1 PLAYER";
		}
		else {
			Controller::gotoXY(50, 18);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 17, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 18);
			cout << "1 PLAYER";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, LIGHT_YELLOW);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 21 + i);
				cout << "              ";
			}
			Controller::gotoXY(52, 22);
			cout << "2 PLAYERS";
		}
		else {
			Controller::gotoXY(50, 22);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 21, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(52, 22);
			cout << "2 PLAYERS";
		}
		if (choice[2]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 25 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 26);
			cout << "BACK";
		}
		else {
			Controller::gotoXY(50, 26);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 25, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(55, 26);
			cout << "BACK";
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

	string filename = Menu::printListFile();
	if (filename != "")
		Game::processLoadFile(filename);

	while (Controller::getConsoleInput() != 6)
	{
		if (Menu::sound_is_open)
			Controller::playSound(ERROR_SOUND);
	}
	if (Menu::sound_is_open)
		Controller::playSound(ENTER_SOUND);
	Menu::goBack();
}

string Menu::printListFile() {
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
	int count = 0;
	char filename[100]; // ten file user luu
	vector<string> arrFilename;
	bool check = true;
	while (listFile.read((char*)filename, 100)) {
		check = false;
		Controller::gotoXY(40, 15 + count);
		cout << filename;
		arrFilename.push_back(filename);
		count++;
		if (count == 11) break;
	}
	if (check) {
		Menu::SetColor(BRIGHT_WHITE, BLACK);
		printRectangle(51, 27, 8, 2);
		Menu::SetColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(49, 28);
		putchar(175);
		Controller::gotoXY(54, 28);
		cout << "Back";
		Controller::gotoXY(62, 28);
		putchar(174);
		return "";
	}

	Menu::printRectangle(80, 14, 30, 4);
	Controller::gotoXY(84, 15);
	Menu::printVietnamese(L"Điền tên FILE cần chơi: ");
	Controller::gotoXY(81, 16);
	for (int i = 0; i < 30; i++) {
		putchar(196);
	}

	bool isRepeat = true;
	do {
		Menu::SetColor(BRIGHT_WHITE, BLACK);
		isRepeat = true;
		Controller::gotoXY(83, 17);
		cin.getline(filename, 100);

		for (int i = 0; i < arrFilename.size(); i++) {
			if (strcmp(filename, arrFilename[i].c_str()) == 0) {
				isRepeat = false;
				break;
			}
		}

		if (isRepeat) {
			Controller::gotoXY(81, 19);
			Menu::SetColor(BRIGHT_WHITE, RED);
			Menu::printVietnamese(L"FILE KHÔNG TỒN TẠI");
		}
		else
		{
			char* temp = new char[100];
			strcpy_s(temp, 100, filename);
			strcpy_s(Game::FILENAME, 100, filename);
			char* temp1 = new char[104];
			int index = 0;
			for (int i = 0; i < 104; i++)
			{
				if (isalpha(temp[i]))
				{
					temp1[i] = temp[i];
				}
				else
				{
					index = i;
					break;
				}
			}
			temp1[index] = '.';
			temp1[index + 1] = 'b';
			temp1[index + 2] = 'i';
			temp1[index + 3] = 'n';
			temp1[index + 4] = '\0';
			return temp1;

		}
		Controller::gotoXY(81, 21);
		Menu::printVietnamese(L"BẠN CÓ MUỐN TIẾP TỤC KHÔNG ?");
		Controller::gotoXY(81, 23);
		cout << "Y: YES" << "\t\t" << "N: NO";
		while (true) {
			int key = Controller::getConsoleInput();
			if (Menu::sound_is_open)
				Controller::playSound(ENTER_SOUND);
			if (key == 10) {
				isRepeat = true;
				Controller::gotoXY(81, 19);
				cout << "                       ";
				Controller::gotoXY(81, 21);
				cout << "                            ";
				Controller::gotoXY(81, 23);
				cout << "      " << "\t\t" << "     ";

				Controller::gotoXY(81, 17);
				for (int i = 0; i < 19; i++) {
					cout << ' ';
				}
				break;
			}
			else if (key == 12) {
				isRepeat = false;
				filename[0] = '\0';

				Controller::gotoXY(81, 21);
				cout << "                         ";
				Controller::gotoXY(81, 23);
				cout << "      " << "\t\t" << "     ";

				Controller::gotoXY(81, 22);
				Menu::printVietnamese(L"ENTER để Trở về");
				Menu::SetColor(BRIGHT_WHITE, BLACK);
				printRectangle(51, 27, 8, 2);
				Menu::SetColor(BRIGHT_WHITE, RED);
				Controller::gotoXY(49, 28);
				putchar(175);
				Controller::gotoXY(53, 28);
				Menu::printVietnamese(L"Trở về");
				Controller::gotoXY(62, 28);
				putchar(174);
				break;
			}
			else
				if (Menu::sound_is_open)
					Controller::playSound(ERROR_SOUND);
		}

	} while (isRepeat);

	return filename;
}