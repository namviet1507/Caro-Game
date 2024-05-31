#include "Struct.h"
#include "Controller.h"
#include "Game.h"
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
	Game::isPlayting = false;
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
			Controller::gotoXY(55, 15);
			cout << "PLAY";
		}
		else {
			Controller::gotoXY(50, 15);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 14, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(55, 15);
			cout << "PLAY";
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
			Controller::gotoXY(55, 21);
			cout << "HELP";
		}
		else {
			Controller::gotoXY(50, 21);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 20, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(55, 21);
			cout << "HELP";
		}

		if (choice[3]) {
			Menu::SetColor(GREEN, BLUE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 23 + i);
				cout << "              ";
			}
			Controller::gotoXY(53, 24);
			cout << "SETTING";
		}
		else {
			Controller::gotoXY(50, 24);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 23, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(53, 24);
			cout << "SETTING";
		}

		if (choice[4]) {
			Menu::SetColor(GREEN, LIGHT_RED);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(50, 26 + i);
				cout << "              ";
			}
			Controller::gotoXY(55, 27);
			cout << "EXIT";
		}
		else {
			Controller::gotoXY(50, 27);
			Menu::SetColor(BRIGHT_WHITE, WHITE);
			cout << "              ";
			Menu::SetColor(BRIGHT_WHITE, LIGHT_GREEN);
			Menu::printRectangle(50, 26, 12, 2);
			Menu::SetColor(BRIGHT_WHITE, GREEN);
			Controller::gotoXY(55, 27);
			cout << "EXIT";
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
	Menu::SetColor(BRIGHT_WHITE, YELLOW);
	fstream file;
	file.open("setting logo.txt", ios::in);
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
						if (Game::isPlayting)
							Game::setupGame();
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
	cout << "Bui Nam Viet - Truong Quang Huy - Truong Hoang Lam" << endl;
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
	Controller::gotoXY(left + 4, top + 5);
	cout << "Moves:";
	Controller::gotoXY(left + 20, top + 1);
	cout << "PLAYER 1: ";
	Controller::gotoXY(left + 22, top + 3);
	putchar(249);
	cout << "'W' : Go Up";
	Controller::gotoXY(left + 22, top + 5);
	putchar(249);
	cout << "'S' : Go Down";
	Controller::gotoXY(left + 22, top + 7);
	putchar(249);
	cout << "'A' : Go Left";
	Controller::gotoXY(left + 22, top + 9);
	putchar(249);
	cout << "'D' : Go Right";
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left + 48, top + 1);
	cout << "PLAYER 2: ";
	Controller::gotoXY(left + 50, top + 3);
	putchar(249);
	cout << "'PgUp' : Go Up";
	Controller::gotoXY(left + 50, top + 5);
	putchar(249);
	cout << "'PgDn' : Go Down";
	Controller::gotoXY(left + 50, top + 7);
	putchar(249);
	cout << "'Home' : Go Left";
	Controller::gotoXY(left + 50, top + 9);
	putchar(249);
	cout << "'End' : Go Right";
	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left + 75, top + 3);
	putchar(249);
	cout << "'U' : Undo";
	Controller::gotoXY(left + 75, top + 5);
	putchar(249);
	cout << "'P' : Pause";
	Controller::gotoXY(left + 75, top + 7);
	putchar(249);
	cout << "'Esc' : Exit";
	Controller::gotoXY(left + 75, top + 9);
	putchar(249);
	cout << "'Enter': Choose";

	Menu::SetColor(BRIGHT_WHITE, LIGHT_RED);
	Controller::gotoXY(left + 5, top + 14);
	cout << "Rules:";
	Controller::gotoXY(left + 17, top + 11);
	int left1 = left + 17;
	putchar(249); cout << " The caro board is 14x14 in size";
	Controller::gotoXY(left1, top + 12);
	putchar(249); cout << " Players alternate turns putting their marks on an empty intersection.";
	Controller::gotoXY(left1, top + 13);
	putchar(249);  cout << " X plays first. The winner is the first player to form an unbroken ";
	Controller::gotoXY(left1, top + 14);
	cout << "  line of 5 marks horizontally, vertically, or diagonally. ";
	Controller::gotoXY(left1, top + 15);
	putchar(249);  cout << " If the board is completely filled and no one can make a line of 5 marks";
	Controller::gotoXY(left1, top + 16);
	cout << "  then it will result in a draw.";

	Menu::SetColor(BRIGHT_WHITE, AQUA);
	Controller::gotoXY(left + 3, top + 19);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 18);
	cout << "Dev 1: Bui Nam Viet (23127516)";
	Controller::gotoXY(left + 31, top + 19);
	cout << "Dev 2: Truong Hoang Lam (23127402)";
	Controller::gotoXY(left + 31, top + 20);
	cout << "Dev 3: Truong Quang Huy (23127530)";

	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 22);
	cout << "Lecturer: ";
	Controller::gotoXY(left + 40, top + 22);
	cout << "Truong Toan Thinh";

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175);
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6)
	{
		if (Menu::sound_is_open)
			Controller::playSound(ERROR_SOUND);
	}
	if (Menu::sound_is_open)
		Controller::playSound(ENTER_SOUND);
	if (Game::isPlayting)
		Game::setupGame();
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
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	printRectangle(51, 27, 8, 2);
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(49, 28);
	putchar(175);
	Controller::gotoXY(54, 28);
	cout << "Back";
	Controller::gotoXY(62, 28);
	putchar(174);

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
	listFile.open(LIST_FILE, ios::in);

	if (!listFile) {
		Menu::SetColor(BLACK, BRIGHT_WHITE);
		system("cls");
		exit(0);
		return "";
	}

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(35, 12, 40, 14);
	Controller::gotoXY(50, 13);
	cout << "List file";
	Controller::gotoXY(36, 14);
	for (int i = 0; i < 39; i++) {
		putchar(196);
	}

	int count = 0;
	string filename = "";
	vector<string> arrFilename;
	while (listFile >> filename) {
		Controller::gotoXY(40, 15 + count);
		cout << filename;
		arrFilename.push_back(filename);
		count++;
		if (count == 11) break;
	}

	Menu::printRectangle(80, 14, 20, 4);
	Controller::gotoXY(84, 15);
	cout << "File you select";
	Controller::gotoXY(81, 16);
	for (int i = 0; i < 19; i++) {
		putchar(196);
	}

	bool isRepeat = true;
	do {
		Menu::SetColor(BRIGHT_WHITE, BLACK);
		isRepeat = true;
		Controller::gotoXY(83, 17);
		getline(cin, filename);


		for (int i = 0; i < arrFilename.size(); i++) {
			if (filename.compare(arrFilename[i]) == 0) {
				isRepeat = false;
				break;
			}
		}

		if (isRepeat) {
			Controller::gotoXY(83, 19);
			Menu::SetColor(BRIGHT_WHITE, RED);
			cout << "File is not available";
		}
		else return "readLoadGame\\" + filename + ".txt";
		Controller::gotoXY(83, 20);
		cout << "Do you want to continue";
		Controller::gotoXY(83, 21);
		cout << "Y: Yes" << '\t' << "N: No";
		while (true) {
			int key = Controller::getConsoleInput();

			if (key == 10) {
				isRepeat = true;

				Controller::gotoXY(83, 20);
				cout << "                       ";
				Controller::gotoXY(83, 21);
				cout << "      " << '\t' << "     ";


				Controller::gotoXY(81, 17);
				for (int i = 0; i < 19; i++) {
					cout << ' ';
				}
				break;
			}
			else if (key == 12) {
				isRepeat = false;
				filename = "";

				Controller::gotoXY(83, 20);
				cout << "                       ";
				Controller::gotoXY(83, 21);
				cout << "      " << '\t' << "     ";

				Controller::gotoXY(83, 20);
				cout << "Click Enter to back";
				break;
			}
		}

	} while (isRepeat);

	return filename;
}