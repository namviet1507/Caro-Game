#include "Game.h"
#include "Struct.h"
#include "Point.h"

Point** Game::board = NULL;
Point* Game::cur_point = NULL;
Point* Game::bot_point = NULL;
stack<Point*> Game::history;

int Game::mode; // 0 là 1 người chơi, 1 là 2 người chơi
bool Game::isPlaying;
bool Game::XWin;
bool Game::isDraw;
bool overTime = false;

char Game::NAMEFILE[100];
char Game::FILENAME[100];
Player a, b;

void Game::setupGame() {
	Game::XWin = false;
	Game::isDraw = false;
	if (Game::mode == 2) {
		Menu::goBack();
	}
	Game::isPlaying = true;
	system("cls");
	system("color F0");
	createBoard();
	cur_point = &board[7][7];
	printBoard();
	printScoreBoard(); // in bảng điểm
	controlPoint();
}

void Game::createBoard() {
	board = new Point * [BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = new Point[BOARD_SIZE];
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j].setRowCol(i, j);
		}
	}
}

void Game::printBoard() {
	int x = BOARD_LEFT;
	int y = BOARD_TOP;
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			Controller::gotoXY(x++, y);
			if (i == 0 && j == 0)
				putchar(218);
			else if (j == 0)
				putchar(195);
			else if (i == 0)
				putchar(194);
			else
				putchar(197);

			for (int k = 0; k < 3; k++) {
				Controller::gotoXY(x++, y);
				putchar(196);
			}

			if (j == BOARD_SIZE - 1 && i == 0)
				putchar(191);
			else if (j == BOARD_SIZE - 1)
				putchar(180);
		}

		x = BOARD_LEFT;
		y++;

		Controller::gotoXY(x++, y);
		putchar(179);

		for (int j = 0; j < BOARD_SIZE; j++) {
			Controller::gotoXY(x++, y);
			putchar(32);
			Controller::gotoXY(x++, y);
			if (Game::board[i][j].sign == 'X')
				Menu::SetColor(BRIGHT_WHITE, COLOR_X);
			else
				Menu::SetColor(BRIGHT_WHITE, COLOR_O);
			cout << Game::board[i][j].sign;
			Menu::SetColor(BRIGHT_WHITE, BLACK);
			Controller::gotoXY(x++, y);
			putchar(32);
			Controller::gotoXY(x++, y);
			putchar(179);
		}

		x = BOARD_LEFT;
		y++;
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		Controller::gotoXY(x++, y);
		if (i == 0)
			putchar(192);
		else
			putchar(193);

		for (int j = 0; j < 3; j++) {
			Controller::gotoXY(x++, y);
			putchar(196);
		}

		if (i == BOARD_SIZE - 1)
			putchar(217);
	}
}

void Game::printScoreBoard() {
	Game::XWin = false;
	Game::isDraw = false;
	overTime = false;
	int x = 65, y = 0;
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(x, y, 42, 28);

	Menu::printRectangle(x + 2, y + 1, 38, 9);
	Controller::gotoXY(x + 4, y + 4);
	Menu::printVietnamese(L"Người chơi 1");
	//cout << "PLAYER 1: ";
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(x + 5, y + 5);
	cout << a.playerName;
	Controller::gotoXY(x, y + 1);
	cout << R"(
											 ___    ___ 
											|\  \  /  /|
											\ \  \/  / /
											 \ \    / / 
											  /     \/  
											 /  /\   \  
											/__/ /\ __\ 
											|__|/ \|__| 
	)";

	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(x + 4, y + 7);
	cout << "Won: " << a.score;

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(x + 2, y + 11, 38, 9);
	Menu::SetColor(BRIGHT_WHITE, LIGHT_BLUE);
	if (mode == 0) {
		Controller::gotoXY(x + 4, y + 14);
		cout << "BOT";
	}
	else {
		Menu::SetColor(BRIGHT_WHITE, BLACK);
		Controller::gotoXY(x + 4, y + 14);
		Menu::printVietnamese(L"Người chơi 2");
		//cout << "PLAYER 2: ";
		Menu::SetColor(BRIGHT_WHITE, LIGHT_BLUE);
		Controller::gotoXY(x + 5, y + 15);
		cout << b.playerName;
	}

	Controller::gotoXY(x, y + 11);
	cout << R"(
											 ________     
											|\   __  \    
											\ \  \|\  \   
											 \ \  \\\  \  
											  \ \  \\\  \ 
											   \ \_______\
										  	    \|_______|
	)";

	Menu::SetColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(x + 4, y + 17);
	cout << "Won: " << b.score;

	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Menu::printRectangle(x + 3, y + 21, 15, 2);
	Controller::gotoXY(x + 7, y + 22);
	Menu::printVietnamese(L"Q: THOÁT");
	//cout << "Q: QUIT";
	Menu::printRectangle(x + 24, y + 21, 15, 2);
	Controller::gotoXY(x + 27, y + 22);
	Menu::printVietnamese(L"L: LƯU GAME");
	//cout << "L: SAVE";
	Menu::printRectangle(x + 3, y + 24, 15, 2);
	Controller::gotoXY(x + 6, y + 25);
	Menu::printVietnamese(L"H: TRỢ GIÚP");
	//cout << "H: HELP";
	Menu::printRectangle(x + 24, y + 24, 15, 2);
	Controller::gotoXY(x + 27, y + 25);
	Menu::printVietnamese(L"M: CÀI ĐẶT");
	//cout << "M: SETTING";
	Menu::SetColor(BRIGHT_WHITE, PURPLE);
	Controller::gotoXY(x + 12, y + 27);
	if (strlen(Game::FILENAME) != 0) {
		Menu::printVietnamese(L"TÊN GAME:  ");
		cout << Game::FILENAME;
	}
}

void Game::printPoint(Point* point, int background, int color) {
	int x = point->getX();
	int y = point->getY();

	Controller::gotoXY(x++, y);
	Menu::SetColor(background, color);
	putchar(32);
	Controller::gotoXY(x++, y);
	cout << point->sign;
	Controller::gotoXY(x, y);
	putchar(32);
}

void Game::controlPoint() {

	// 1 người chơi
	if (Game::mode == 0) {
		int mid = (0 + BOARD_SIZE - 1) / 2;
		bot_point = &board[mid][mid];
		bot_point->sign = 'O';
		printPoint(bot_point, BRIGHT_WHITE, BLUE);
	}

	char last_sign = 'O';
	int timeLeft = 15;
	time_t originalTime = time(0);
	if (Menu::music_is_open)
		Controller::playSound(7);
	while (true) {
		Game::countdown(last_sign, originalTime, timeLeft, overTime);
		if (overTime) {
			Controller::playSound(ERROR_SOUND);
			Menu::SetColor(RED, BRIGHT_WHITE);
			if (last_sign == 'O') {
				Controller::gotoXY(69, 9);
				cout << " LOSE TURN ";
				Sleep(1000);
				Controller::gotoXY(69, 9);
				Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
				cout << "           ";
			}
			else {
				Controller::gotoXY(69, 19);
				cout << " LOSE TURN ";
				Sleep(1000);
				Controller::gotoXY(69, 19);
				Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
				cout << "           ";
			}
			overTime = false;
			timeLeft = 15;
			originalTime = time(0);
			if (Game::mode == 0) {
				processBotHard();

				bot_point->sign = 'O';

				history.push(bot_point);

				if (bot_point->sign == 'X')
					printPoint(bot_point, BRIGHT_WHITE, RED);
				else if (bot_point->sign == 'O')
					printPoint(bot_point, BRIGHT_WHITE, BLUE);
				else
					printPoint(bot_point, BRIGHT_WHITE, BLACK);

				int direction_win = 0;
				if (checkWinGameCol(bot_point))
					direction_win = 1;
				else if (checkWinGameRow(bot_point))
					direction_win = 2;
				else if (checkWinGameDM(bot_point))
					direction_win = 3;
				else if (checkWinGameDS(bot_point))
					direction_win = 4;

				if (direction_win != 0) {

					if (bot_point->sign == 'X')
						printPoint(bot_point, BRIGHT_WHITE, RED);
					else if (bot_point->sign == 'O')
						printPoint(bot_point, BRIGHT_WHITE, BLUE);
					else
						printPoint(bot_point, BRIGHT_WHITE, BLACK);

					processWinGame(direction_win, bot_point);

					b.score++;

					resetGame();
					break;
				}
			}
			else {
				if (last_sign == 'O')
					last_sign = 'X';
				else if (last_sign == 'X')
					last_sign = 'O';
			}
			continue;
		}

		if (cur_point->sign == 'X')
			printPoint(cur_point, YELLOW, RED);
		else if (cur_point->sign == 'O')
			printPoint(cur_point, YELLOW, BLUE);
		else
			printPoint(cur_point, YELLOW, BLACK);

		if (_kbhit()) {
			switch (Controller::getConsoleInput()) {
			case 1: // esc
				Menu::SetColor(BLACK, BRIGHT_WHITE);
				system("cls");
				exit(0);
				return;
			case 2: // up
				if (cur_point->row > 0) {

					if (cur_point->sign == 'X')
						printPoint(cur_point, BRIGHT_WHITE, RED);
					else if (cur_point->sign == 'O')
						printPoint(cur_point, BRIGHT_WHITE, BLUE);
					else
						printPoint(cur_point, BRIGHT_WHITE, BLACK);

					cur_point = &board[cur_point->row - 1][cur_point->col];
				}
				break;
			case 3: // left
				if (cur_point->col > 0) {

					if (cur_point->sign == 'X')
						printPoint(cur_point, BRIGHT_WHITE, RED);
					else if (cur_point->sign == 'O')
						printPoint(cur_point, BRIGHT_WHITE, BLUE);
					else
						printPoint(cur_point, BRIGHT_WHITE, BLACK);

					cur_point--;
				}
				break;
			case 4: // right
				if (cur_point->col < BOARD_SIZE - 1) {

					if (cur_point->sign == 'X')
						printPoint(cur_point, BRIGHT_WHITE, RED);
					else if (cur_point->sign == 'O')
						printPoint(cur_point, BRIGHT_WHITE, BLUE);
					else
						printPoint(cur_point, BRIGHT_WHITE, BLACK);

					cur_point++;
				}
				break;
			case 5: // down
				if (cur_point->row < BOARD_SIZE - 1) {

					if (cur_point->sign == 'X')
						printPoint(cur_point, BRIGHT_WHITE, RED);
					else if (cur_point->sign == 'O')
						printPoint(cur_point, BRIGHT_WHITE, BLUE);
					else
						printPoint(cur_point, BRIGHT_WHITE, BLACK);

					cur_point = &board[cur_point->row + 1][cur_point->col];
				}
				break;
			case 6:
				if (cur_point->sign == ' ') {
					timeLeft = 15;
					originalTime = time(0);
					if (Menu::sound_is_open)
						Controller::playSound(ENTER_SOUND);
					if (Game::mode == 1) {
						if (last_sign == 'O') {
							cur_point->sign = 'X';
							last_sign = 'X';
						}
						else if (last_sign == 'X') {
							cur_point->sign = 'O';
							last_sign = 'O';
						}

						history.push(cur_point);

						int direction_win = 0;

						// lấy chiều các điểm để win
						if (checkWinGameCol(cur_point))
							direction_win = 1;
						else if (checkWinGameRow(cur_point))
							direction_win = 2;
						else if (checkWinGameDM(cur_point))
							direction_win = 3;
						else if (checkWinGameDS(cur_point))
							direction_win = 4;

						if (direction_win != 0) {
							if (cur_point->sign == 'X')
								printPoint(cur_point, BRIGHT_WHITE, RED);
							else if (cur_point->sign == 'O')
								printPoint(cur_point, BRIGHT_WHITE, BLUE);
							else
								printPoint(cur_point, BRIGHT_WHITE, BLACK);

							processWinGame(direction_win, cur_point);

							if (cur_point->sign == 'X')
								a.score++;
							else if (cur_point->sign == 'O')
								b.score++;

							resetGame();
							break;
						}
					}
					else if (Game::mode == 0) {
						// 1 người chơi
						cur_point->sign = 'X';

						history.push(cur_point);

						if (cur_point->sign == 'X')
							printPoint(cur_point, BRIGHT_WHITE, RED);
						else if (cur_point->sign == 'O')
							printPoint(cur_point, BRIGHT_WHITE, BLUE);
						else
							printPoint(cur_point, BRIGHT_WHITE, BLACK);

						int direction_win = 0;

						// lấy chiều các điểm để win
						if (checkWinGameCol(cur_point))
							direction_win = 1;
						else if (checkWinGameRow(cur_point))
							direction_win = 2;
						else if (checkWinGameDM(cur_point))
							direction_win = 3;
						else if (checkWinGameDS(cur_point))
							direction_win = 4;

						if (direction_win != 0) {
							if (cur_point->sign == 'X')
								printPoint(cur_point, BRIGHT_WHITE, RED);
							else if (cur_point->sign == 'O')
								printPoint(cur_point, BRIGHT_WHITE, BLUE);
							else
								printPoint(cur_point, BRIGHT_WHITE, BLACK);

							processWinGame(direction_win, cur_point);

							a.score++;

							resetGame();
							break;
						}

						// lượt của bot
						//processBot();
						processBotHard();

						bot_point->sign = 'O';

						history.push(bot_point);

						if (bot_point->sign == 'X')
							printPoint(bot_point, BRIGHT_WHITE, RED);
						else if (bot_point->sign == 'O')
							printPoint(bot_point, BRIGHT_WHITE, BLUE);
						else
							printPoint(bot_point, BRIGHT_WHITE, BLACK);


						if (checkWinGameCol(bot_point))
							direction_win = 1;
						else if (checkWinGameRow(bot_point))
							direction_win = 2;
						else if (checkWinGameDM(bot_point))
							direction_win = 3;
						else if (checkWinGameDS(bot_point))
							direction_win = 4;

						if (direction_win != 0) {

							if (bot_point->sign == 'X')
								printPoint(bot_point, BRIGHT_WHITE, RED);
							else if (bot_point->sign == 'O')
								printPoint(bot_point, BRIGHT_WHITE, BLUE);
							else
								printPoint(bot_point, BRIGHT_WHITE, BLACK);

							processWinGame(direction_win, bot_point);

							b.score++;

							resetGame();
							break;
						}
					}

					if (checkDraw()) {
						/*Controller::gotoXY(60, 15);
						Menu::SetColor(GREEN, BRIGHT_WHITE);
						cout << "Draw";*/
						if (Menu::music_is_open)
							Controller::playSound(LOSE_SOUND);
						Sleep(1000);
						Game::isDraw = true;
						resetGame();
					}
				}
				else {
					if (Menu::sound_is_open)
						Controller::playSound(ERROR_SOUND);
				}
				break;
			case 7: // Help
				Menu::helpScreen();
				break;
			case 8: // Quit
				Game::FILENAME[0] = '\0';
				a.playerName[0] = '\0';
				b.playerName[0] = '\0';
				a.score = 0;
				b.score = 0;
				Menu::goBack();
				break;
			case 9: // L, l
				processSaveFile(last_sign);
				break;
			case 11: // Setting
				Menu::Setting();
				break;
			case 14: // Undo
				UndoStep(last_sign);
				break;
			default:
				break;
			}
		}
	}
}

void Game::resetGame() {
	while (!history.empty())
		history.pop();
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	system("cls");
	Game::isPlaying = false;
	if (Game::isDraw) {
		Menu::SetColor(BRIGHT_WHITE, GREEN);
		Controller::gotoXY(0, 3);
		cout << R"(
				/$$$$$$$  /$$$$$$$   /$$$$$$  /$$      /$$
				| $$__  $$| $$__  $$ /$$__  $$| $$  /$ | $$
				| $$  \ $$| $$  \ $$| $$  \ $$| $$ /$$$| $$
				| $$  | $$| $$$$$$$/| $$$$$$$$| $$/$$ $$ $$
				| $$  | $$| $$__  $$| $$__  $$| $$$$_  $$$$
				| $$  | $$| $$  \ $$| $$  | $$| $$$/ \  $$$
				| $$$$$$$/| $$  | $$| $$  | $$| $$/   \  $$
				|_______/ |__/  |__/|__/  |__/|__/     \__/
			)";
	}
	else {
		if (Game::XWin) {
			Menu::SetColor(BRIGHT_WHITE, RED);
			Controller::gotoXY(0, 5);
			cout << R"(
				 ___    ___      ___       __   ___  ________      
				|\  \  /  /|    |\  \     |\  \|\  \|\   ___  \    
				\ \  \/  / /    \ \  \    \ \  \ \  \ \  \\ \  \   
				 \ \    / /      \ \  \  __\ \  \ \  \ \  \\ \  \  
				  /     \/        \ \  \|\__\_\  \ \  \ \  \\ \  \ 
				 /  /\   \         \ \____________\ \__\ \__\\ \__\
				/__/ /\ __\         \|____________|\|__|\|__| \|__|
				|__|/ \|__|                                        
			)";
		}
		else {
			Menu::SetColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(0, 5);
			cout << R"(
				  /$$$$$$        /$$      /$$ /$$$$$$ /$$   /$$
				 /$$__  $$      | $$  /$ | $$|_  $$_/| $$$ | $$
				| $$  \ $$      | $$ /$$$| $$  | $$  | $$$$| $$
				| $$  | $$      | $$/$$ $$ $$  | $$  | $$ $$ $$
				| $$  | $$      | $$$$_  $$$$  | $$  | $$  $$$$
				| $$  | $$      | $$$/ \  $$$  | $$  | $$\  $$$
				|  $$$$$$/      | $$/   \  $$ /$$$$$$| $$ \  $$
				 \______/       |__/     \__/|______/|__/  \__/
			)";
		}
	}
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(33, 17, 45, 8);
	Controller::gotoXY(44, 19);
	Menu::printVietnamese(L"BẠN CÓ MUỐN CHƠI TIẾP KHÔNG ?");
	int choice[2] = { 0,0 }, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(40, 21 + i);
				cout << "           ";
			}
			Controller::gotoXY(44, 22);
			Menu::printVietnamese(L"CÓ");
		}
		else {
			Controller::gotoXY(40, 22);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "           ";
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Menu::printRectangle(40, 21, 9, 2);
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Controller::gotoXY(44, 22);
			Menu::printVietnamese(L"CÓ");
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(62, 21 + i);
				cout << "           ";
			}
			Controller::gotoXY(66, 22);
			Menu::printVietnamese(L"KHÔNG");
		}
		else {
			Controller::gotoXY(62, 22);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "           ";
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Menu::printRectangle(62, 21, 9, 2);
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Controller::gotoXY(66, 22);
			Menu::printVietnamese(L"KHÔNG");
		}
		int temp, key;
		if (temp = _getch()) {
			if (temp != 224 && temp)
			{
				if (temp == KEY_ENTER) {
					if (curChoice == 0) {
						Game::setupGame();
						break;
					}
					else {
						Game::FILENAME[0] = '\0';
						a.playerName[0] = '\0';
						b.playerName[0] = '\0';
						a.score = 0;
						b.score = 0;
						Menu::printMainScreen();
					}
				}
			}
			else {
				key = _getch();
				Controller::playSound(MOVE_SOUND);
				switch (key)
				{
				case KEY_LEFT:
					choice[curChoice] = 0;
					if (curChoice > 0) curChoice--;
					else curChoice = 1;
					break;
				case KEY_RIGHT:
					choice[curChoice] = 0;
					if (curChoice < 1) curChoice++;
					else curChoice = 0;
				default:
					break;
				}
			}
		}
	}
}

void Game::UndoStep(char& last_sign) {
	if (history.empty()) {
		if (Menu::sound_is_open) Controller::playSound(ERROR_SOUND);
		return;
	}
	if (mode == 0) {
		// 1 nguoi choi
		Point* mark = history.top();
		history.pop();
		mark->sign = ' ';
		printPoint(mark, BRIGHT_WHITE, BLACK);

		mark = history.top();
		history.pop();
		mark->sign = ' ';
		if (Menu::sound_is_open)
			Controller::playSound(MATCH_SOUND);

		if (mark == cur_point) {
			printPoint(mark, YELLOW, BLACK);
		}
		else {
			printPoint(mark, BRIGHT_WHITE, BLACK);
		}
	}
	else {
		if (last_sign == '0') last_sign = 'X';
		else if (last_sign == 'X') last_sign = 'O';

		Point* mark = history.top();
		history.pop();
		mark->sign = ' ';
		if (Menu::sound_is_open)
			Controller::playSound(MATCH_SOUND);

		if (mark == cur_point) {
			printPoint(mark, YELLOW, BLACK);
		}
		else {
			printPoint(mark, BRIGHT_WHITE, BLACK);
		}
	}
}

void Game::getScore(int score[4][BOARD_SIZE][BOARD_SIZE], char sign) {
	// ngang
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].sign == ' ') {
				int t = 0;
				for (int k = 1; k < 5; k++) {
					if (j + k < BOARD_SIZE) {
						if (board[i][j + k].sign == ' ') continue;
						else if (board[i][j + k].sign == sign) t += 5 - k;
						else break;
					}
				}

				for (int k = 1; k < 5; k++) {
					if (j - k >= 0) {
						if (board[i][j - k].sign == ' ') continue;
						else if (board[i][j - k].sign == sign) t += 5 - k;
						else break;
					}
				}

				score[0][i][j] = t;
			}
		}
	}

	// doc
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].sign == ' ') {
				int t = 0;
				for (int k = 1; k < 5; k++) {
					if (i + k < BOARD_SIZE) {
						if (board[i + k][j].sign == ' ') continue;
						else if (board[i + k][j].sign == sign) t += 5 - k;
						else break;
					}
				}

				for (int k = 1; k < 5; k++) {
					if (i - k >= 0) {
						if (board[i - k][j].sign == ' ') continue;
						else if (board[i - k][j].sign == sign) t += 5 - k;
						else break;
					}
				}

				score[1][i][j] = t;
			}
		}
	}

	// cheo chinh
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].sign == ' ') {
				int t = 0;
				for (int k = 1; k < 5; k++) {
					if (i + k < BOARD_SIZE && j + k < BOARD_SIZE) {
						if (board[i + k][j + k].sign == ' ') continue;
						else if (board[i + k][j + k].sign == sign) t += 5 - k;
						else break;
					}
				}

				for (int k = 1; k < 5; k++) {
					if (i - k >= 0 && j - k >= 0) {
						if (board[i - k][j - k].sign == ' ') continue;
						else if (board[i - k][j - k].sign == sign) t += 5 - k;
						else break;
					}
				}

				score[2][i][j] = t;
			}
		}
	}

	// cheo phu
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].sign == ' ') {
				int t = 0;
				for (int k = 1; k < 5; k++) {
					if (i + k < BOARD_SIZE && j - k >= 0) {
						if (board[i + k][j - k].sign == ' ') continue;
						else if (board[i + k][j - k].sign == sign) t += 5 - k;
						else break;
					}
				}

				for (int k = 1; k < 5; k++) {
					if (i - k >= 0 && j + k < BOARD_SIZE) {
						if (board[i - k][j + k].sign == ' ') continue;
						else if (board[i - k][j + k].sign == sign) t += 5 - k;
						else break;
					}
				}

				score[3][i][j] = t;
			}
		}
	}
}

void Game::processBotHard() {
	int atk[4][BOARD_SIZE][BOARD_SIZE] = { 0 };
	int def[4][BOARD_SIZE][BOARD_SIZE] = { 0 };

	// 0 ngang, 1 doc, 2 cheo chinh, 3 cheo phu
	getScore(atk, bot_point->sign);
	getScore(def, cur_point->sign);

	Point* atk_point = &board[0][0]; int max_atk = atk[0][0][0];
	Point* def_point = &board[0][0]; int max_def = def[0][0][0];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			for (int k = 0; k < BOARD_SIZE; k++) {
				if (max_atk < atk[i][j][k]) {
					max_atk = atk[i][j][k];
					atk_point = &board[j][k];
				}
				if (max_def < def[i][j][k]) {
					max_def = def[i][j][k];
					def_point = &board[j][k];
				}
			}
		}
	}

	if (max_atk >= max_def) bot_point = atk_point;
	else bot_point = def_point;
}

void Game::processBot() {
	int row = cur_point->row;
	int col = cur_point->col;

	int size = 3;
	while (true) {
		bool increaseSize = true;
		for (int i = -size / 2; i <= size / 2; i++) {
			if (increaseSize == false) break;
			for (int j = -size / 2; j <= size / 2; j++) {
				if (row + i < 0 || row + i > BOARD_SIZE - 1) continue;
				if (col + j < 0 || col + j > BOARD_SIZE - 1) continue;
				if (board[row + i][col + j].sign == ' ') {
					increaseSize = false;
					break;
				}
			}
		}

		if (increaseSize) {
			size += 1;
			continue;
		}

		int r_change = rand() % size - 1;
		int c_change = rand() % size - 1;

		while (true) {
			r_change = rand() % size - 1;
			c_change = rand() % size - 1;
			if (row + r_change < 0 || row + r_change > BOARD_SIZE - 1) continue;
			if (col + c_change < 0 || col + c_change > BOARD_SIZE - 1) continue;
			if (r_change != 0 || c_change != 0) break;
		}

		if (board[row + r_change][col + c_change].sign == ' ') {
			bot_point = &board[row + r_change][col + c_change];
			break;
		}
	}
}

void Game::processWinGame(int direction, Point* point) {
	char sign = point->sign;

	if (direction == 1) {
		// chiều dọc
		for (int i = 0; i < 4; i++) {
			if (point->row == 0) break;
			if (board[point->row - 1][point->col].sign != sign) break;
			point = &board[point->row - 1][point->col];
		}
		if (point->sign == 'X')
			printPoint(point, RED, BRIGHT_WHITE);
		else
			printPoint(point, BLUE, BRIGHT_WHITE);

		for (int i = 0; i < 4; i++) {
			point = &board[point->row + 1][point->col];
			if (point->sign == 'X')
				printPoint(point, RED, BRIGHT_WHITE);
			else
				printPoint(point, BLUE, BRIGHT_WHITE);
		}
	}
	else if (direction == 2) {
		// chiều ngang
		for (int i = 0; i < 4; i++) {
			if (point->col == 0) break;
			if (board[point->row][point->col - 1].sign != sign) break;
			point = &board[point->row][point->col - 1];
		}

		if (point->sign == 'X')
			printPoint(point, RED, BRIGHT_WHITE);
		else
			printPoint(point, BLUE, BRIGHT_WHITE);

		for (int i = 0; i < 4; i++) {
			point = &board[point->row][point->col + 1];
			if (point->sign == 'X')
				printPoint(point, RED, BRIGHT_WHITE);
			else
				printPoint(point, BLUE, BRIGHT_WHITE);
		}
	}
	else if (direction == 3) {
		// đường chéo (dấu huyền)
		for (int i = 0; i < 4; i++) {
			if (point->col == 0 || point->row == 0) break;
			if (board[point->row - 1][point->col - 1].sign != sign) break;
			point = &board[point->row - 1][point->col - 1];
		}
		if (point->sign == 'X')
			printPoint(point, RED, BRIGHT_WHITE);
		else
			printPoint(point, BLUE, BRIGHT_WHITE);

		for (int i = 0; i < 4; i++) {
			point = &board[point->row + 1][point->col + 1];
			if (point->sign == 'X')
				printPoint(point, RED, BRIGHT_WHITE);
			else
				printPoint(point, BLUE, BRIGHT_WHITE);
		}
	}
	else if (direction == 4) {
		//đường chéo (dấu sắc)
		for (int i = 0; i < 4; i++) {
			if (point->col == BOARD_SIZE - 1 || point->row == 0) break;
			if (board[point->row - 1][point->col + 1].sign != sign) break;
			point = &board[point->row - 1][point->col + 1];
		}

		if (point->sign == 'X')
			printPoint(point, RED, BRIGHT_WHITE);
		else
			printPoint(point, BLUE, BRIGHT_WHITE);

		for (int i = 0; i < 4; i++) {
			point = &board[point->row + 1][point->col - 1];
			if (point->sign == 'X')
				printPoint(point, RED, BRIGHT_WHITE);
			else
				printPoint(point, BLUE, BRIGHT_WHITE);
		}
	}

	if (Menu::music_is_open)
		Controller::playSound(WIN_SOUND);

	if (point->sign == 'X') {
		Game::XWin = true;
		int cnt = 30;
		while (cnt--) {
			Controller::gotoXY(115, 10);
			Menu::SetColor(BRIGHT_WHITE, rand() % 6);
			cout << R"(
								 ___    ___      ___       __   ___  ________      
								|\  \  /  /|    |\  \     |\  \|\  \|\   ___  \    
								\ \  \/  / /    \ \  \    \ \  \ \  \ \  \\ \  \   
								 \ \    / /      \ \  \  __\ \  \ \  \ \  \\ \  \  
								  /     \/        \ \  \|\__\_\  \ \  \ \  \\ \  \ 
								 /  /\   \         \ \____________\ \__\ \__\\ \__\
								/__/ /\ __\         \|____________|\|__|\|__| \|__|
								|__|/ \|__|                                        
							)";
			Sleep(200);
		}
	}
	else {
		Game::XWin = false;
		int cnt = 30;
		while (cnt--) {
			Controller::gotoXY(115, 10);
			Menu::SetColor(BRIGHT_WHITE, rand() % 6);
			cout << R"(
								  /$$$$$$        /$$      /$$ /$$$$$$ /$$   /$$
								 /$$__  $$      | $$  /$ | $$|_  $$_/| $$$ | $$
								| $$  \ $$      | $$ /$$$| $$  | $$  | $$$$| $$
								| $$  | $$      | $$/$$ $$ $$  | $$  | $$ $$ $$
								| $$  | $$      | $$$$_  $$$$  | $$  | $$  $$$$
								| $$  | $$      | $$$/ \  $$$  | $$  | $$\  $$$
								|  $$$$$$/      | $$/   \  $$ /$$$$$$| $$ \  $$
								 \______/       |__/     \__/|______/|__/  \__/
							)";
			Sleep(200);
		}
	}
}

bool Game::checkDraw() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j].sign == ' ') return false;
		}
	}
	return true;
}

bool Game::checkWinGameCol(Point* point) {
	char sign = point->sign;
	int col = point->col;

	while (point->row > 0) {
		point = &board[point->row - 1][point->col];
		if (point->sign != sign) {
			point = &board[point->row + 1][point->col];
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (point->row + 1 == BOARD_SIZE) {
			return false;
		}
		point = &board[point->row + 1][point->col];
		if (point->sign != sign) return false;
	}
	return true;
}

bool Game::checkWinGameRow(Point* point) {
	char sign = point->sign;

	while (point->col > 0) {
		point--;
		if (point->sign != sign) {
			point++;
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (point->col + 1 == BOARD_SIZE) {
			return false;
		}
		point++;
		if (point->sign != sign) {
			return false;
		}
	}
	return true;
}

bool Game::checkWinGameDM(Point* point) {
	char sign = point->sign;

	while (point->col > 0 && point->row > 0) {
		point = &board[point->row - 1][point->col - 1];
		if (point->sign != sign) {
			point = &board[point->row + 1][point->col + 1];
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (point->col == BOARD_SIZE - 1 || point->row == BOARD_SIZE - 1) return false;
		point = &board[point->row + 1][point->col + 1];
		if (point->sign != sign) return false;
	}
	return true;
}

bool Game::checkWinGameDS(Point* point) {
	char sign = point->sign;

	while (point->col > 0 && point->row < BOARD_SIZE - 1) {
		point = &board[point->row + 1][point->col - 1];
		if (point->sign != sign) {
			point = &board[point->row - 1][point->col + 1];
			break;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (point->col + 1 == BOARD_SIZE || point->row == 0) return false;
		point = &board[point->row - 1][point->col + 1];
		if (point->sign != sign) return false;
	}
	return true;
}

void Game::processSaveFile(char last_sign) {
	Menu::SetColor(BRIGHT_WHITE, PURPLE);
	Menu::printRectangle(55, 12, 30, 6);
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Controller::gotoXY(56, 13);
	for (int i = 0; i < 5; i++) {
		Controller::gotoXY(56, 13 + i);
		for (int j = 0; j < 29; j++)
			cout << ' ';
	}
	if (strlen(Game::FILENAME) != 0) {
		int choice[2] = { 0,0 }, curChoice = 0;
		while (true) {
			choice[curChoice] = 1;
			if (choice[0]) {
				Menu::SetColor(GREEN, BRIGHT_WHITE);
				for (int i = 0; i < 3; i++) {
					Controller::gotoXY(58, 14 + i);
					cout << "           ";
				}
				Controller::gotoXY(62, 15);
				Menu::printVietnamese(L"LƯU");
			}
			else {
				Controller::gotoXY(59, 15);
				Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
				cout << "           ";
				Menu::SetColor(BRIGHT_WHITE, PURPLE);
				Menu::printRectangle(58, 14, 9, 2);
				Menu::SetColor(BRIGHT_WHITE, PURPLE);
				Controller::gotoXY(62, 15);
				Menu::printVietnamese(L"LƯU");
			}
			if (choice[1]) {
				Menu::SetColor(GREEN, BRIGHT_WHITE);
				for (int i = 0; i < 3; i++) {
					Controller::gotoXY(70, 14 + i);
					cout << "              ";
				}
				Controller::gotoXY(72, 15);
				Menu::printVietnamese(L"LƯU THÀNH");
			}
			else {
				Controller::gotoXY(71, 15);
				Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
				cout << "              ";
				Menu::SetColor(BRIGHT_WHITE, PURPLE);
				Menu::printRectangle(70, 14, 12, 2);
				Menu::SetColor(BRIGHT_WHITE, PURPLE);
				Controller::gotoXY(72, 15);
				Menu::printVietnamese(L"LƯU THÀNH");
			}
			int temp, key;
			if (temp = _getch()) {
				if (temp != 224 && temp)
				{
					if (temp == KEY_ENTER) {
						if (curChoice == 0) {
							fstream outFile;
							string tt = ".bin";
							string pmet = Game::FILENAME + tt;
							outFile.open("readLoadGame/" + pmet, ios::out | ios::binary);

							outFile.write((char*)&a.playerName, sizeof(a.playerName));

							outFile.write((char*)&a.score, sizeof(a.score));

							outFile.write((char*)&b.playerName, sizeof(b.playerName));

							outFile.write((char*)&b.score, sizeof(b.score));

							outFile.write((char*)&mode, sizeof(mode));

							outFile.write((char*)&cur_point->row, sizeof(cur_point->row));
							outFile.write((char*)&cur_point->col, sizeof(cur_point->col));

							outFile.write((char*)&last_sign, sizeof(last_sign));

							size_t history_size = history.size();
							outFile.write((char*)&history_size, sizeof(history_size));

							while (history.empty() == false) {

								Point* ptr_point = history.top();

								outFile.write((char*)&ptr_point->row, sizeof(ptr_point->row));
								outFile.write((char*)&ptr_point->col, sizeof(ptr_point->col));
								outFile.write((char*)&ptr_point->sign, sizeof(ptr_point->sign));

								history.pop();
							}

							outFile.close();
							system("cls");
							Game::printBoard();
							Game::printScoreBoard();
							return;
						}
						else {
							break;
						}
					}
				}
				else {
					key = _getch();
					Controller::playSound(MOVE_SOUND);
					switch (key)
					{
					case KEY_LEFT:
						choice[curChoice] = 0;
						if (curChoice > 0) curChoice--;
						else curChoice = 1;
						break;
					case KEY_RIGHT:
						choice[curChoice] = 0;
						if (curChoice < 1) curChoice++;
						else curChoice = 0;
					default:
						break;
					}
				}
			}
		}
	}

	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Controller::gotoXY(56, 13);
	for (int i = 0; i < 5; i++) {
		Controller::gotoXY(56, 13 + i);
		for (int j = 0; j < 29; j++)
			cout << ' ';
	}
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(64, 13);
	Menu::printVietnamese(L"NHẬP TÊN FILE");
	//cout << "Input your file name";
	Menu::SetColor(RED, BRIGHT_WHITE);
	Controller::gotoXY(55, 20);
	Menu::printVietnamese(L"NHẬP TÊN FILE ÍT HƠN 15 KÝ TỰ !");
	//cout << "  Please enter your file under 15 characters!  ";
	Menu::SetColor(BRIGHT_WHITE, PURPLE);
	Controller::gotoXY(56, 14);
	for (int i = 0; i < 30; i++)
		putchar(196);

	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(58, 16);
	cin.getline(Game::NAMEFILE, 100);
	strcpy_s(Game::FILENAME, 100, Game::NAMEFILE);
	Controller::gotoXY(58, 16);
	cout << "                            ";

	while (strlen(Game::NAMEFILE) > 15 || strlen(Game::NAMEFILE) == 0) {
		if (Menu::sound_is_open)
			Controller::playSound(ERROR_SOUND);

		Controller::gotoXY(58, 16);
		cout << "                            ";

		Controller::gotoXY(58, 16);
		cin.getline(Game::NAMEFILE, 100);

		strcpy_s(Game::FILENAME, 100, Game::NAMEFILE);
		Controller::gotoXY(58, 16);
		cout << "                            ";
	}



	if (strlen(Game::NAMEFILE) > 15) {
		if (Menu::sound_is_open)
			Controller::playSound(ERROR_SOUND);
		system("cls");
		Game::printBoard();
		Game::printScoreBoard();
		Game::processSaveFile(last_sign);
		return;
	}
	else {
		fstream listFile;
		listFile.open(LIST_FILE, ios::in | ios::binary);
		char tenfile[100];
		while (listFile.read((char*)tenfile, 100)) {
			if (strcmp(tenfile, Game::NAMEFILE) == 0) {
				Controller::gotoXY(63, 17);
				Menu::SetColor(RED, BRIGHT_WHITE);
				Menu::printVietnamese(L"FILE ĐÃ TỒN TẠI !");
				//cout << "File already exists !";
				if (Menu::sound_is_open)
					Controller::playSound(ERROR_SOUND);
				Sleep(500);
				Game::FILENAME[0] = '\0';
				Game::processSaveFile(last_sign);
				return;
			}
		}
		listFile.close();
	}

	fstream listFile;
	listFile.open(LIST_FILE, ios::app | ios::binary);
	if (!listFile) {
		freeBoard();
		Menu::SetColor(BLACK, BRIGHT_WHITE);
		system("cls");
		exit(0);
		return;
	}
	listFile.write((char*)&Game::NAMEFILE, sizeof(Game::NAMEFILE));
	listFile.close();

	string bb = ".bin";
	string gan = Game::NAMEFILE + bb;

	fstream outFile;

	outFile.open("readLoadGame/" + gan, ios::out | ios::binary);

	outFile.write((char*)&a.playerName, sizeof(a.playerName));

	outFile.write((char*)&a.score, sizeof(a.score));

	outFile.write((char*)&b.playerName, sizeof(b.playerName));

	outFile.write((char*)&b.score, sizeof(b.score));

	outFile.write((char*)&mode, sizeof(mode));

	outFile.write((char*)&cur_point->row, sizeof(cur_point->row));
	outFile.write((char*)&cur_point->col, sizeof(cur_point->col));

	outFile.write((char*)&last_sign, sizeof(last_sign));

	size_t history_size = history.size();
	outFile.write((char*)&history_size, sizeof(history_size));

	while (history.empty() == false) {
		Point* ptr_point = history.top();

		outFile.write((char*)&ptr_point->row, sizeof(ptr_point->row));
		outFile.write((char*)&ptr_point->col, sizeof(ptr_point->col));
		outFile.write((char*)&ptr_point->sign, sizeof(ptr_point->sign));

		history.pop();
	}
	outFile.close();

	Controller::gotoXY(57, 13);
	cout << "                            ";
	Controller::gotoXY(57, 15);
	cout << "                            ";

	Controller::gotoXY(57, 13);
	Menu::printVietnamese(L"BẠN CÓ MUỐN CHƠI TIẾP KHÔNG ?");
	//cout << "Do you want to continue?";
	Menu::printRectangle(58, 15, 10, 2);
	Controller::gotoXY(61, 16);
	Menu::printVietnamese(L"Y: CÓ");
	//cout << "Y: YES";
	Menu::printRectangle(73, 15, 10, 2);
	Controller::gotoXY(75, 16);
	Menu::printVietnamese(L"N: KHÔNG");
	//cout << "N: NO";

	while (true) {
		int key = Controller::getConsoleInput();

		if (key == 10) {
			system("cls");
			printBoard();
			printScoreBoard();
			break;
		}
		else if (key == 12) {
			Game::FILENAME[0] = '\0';
			Game::NAMEFILE[0] = '\0';
			freeBoard();
			Menu::goBack();
		}
	}
}

void Game::freeBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		delete[] board[i];
	}
	delete[] board;
}

void Game::processLoadFile(string filename) {
	fstream inFile;

	inFile.open("readLoadGame/" + filename, ios::in | ios::binary);

	if (!inFile) return;

	int row, col;
	char last_sign, sign;
	size_t size;

	inFile.read((char*)&a.playerName, sizeof(a.playerName));

	inFile.read((char*)&a.score, sizeof(a.score));

	inFile.read((char*)&b.playerName, sizeof(b.playerName));

	inFile.read((char*)&b.score, sizeof(b.score));

	inFile.read((char*)&mode, sizeof(mode));

	inFile.read((char*)&row, sizeof(row));
	inFile.read((char*)&col, sizeof(col));
	inFile.read((char*)&last_sign, sizeof(last_sign));
	inFile.read((char*)&size, sizeof(size));
	createBoard();
	cur_point = &board[row][col];
	for (int i = 0; i < size; i++) {

		inFile.read((char*)&row, sizeof(row));
		inFile.read((char*)&col, sizeof(col));
		inFile.read((char*)&sign, sizeof(sign));
		board[row][col].sign = sign;
		history.push(&board[row][col]);
	}

	while (history.empty() == false) {
		history.pop();
	}

	system("cls");
	system("color F0");
	printBoard();
	printScoreBoard(); // in bảng điểm
	Game::isPlaying = true;
	controlPoint();

	inFile.close();
}

void Game::signup() {
	system("cls");
	Menu::printLogoStandard();
	Menu::SetColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(28, 16);
	Menu::printVietnamese(L"Nhập tên của bạn ngắn thôi nha, ít hơn 10 ký tự");
	//cout << "Please enter your name shortly, under 10 characters!";
	Menu::SetColor(BRIGHT_WHITE, LIGHT_BLUE);
	Controller::gotoXY(35, 18);
	Menu::printVietnamese(L"Nhập tên:  ");
	//cout << "Enter your name: ";
	if (Game::mode == 0) {
		cin.getline(a.playerName, 100);
		if (strcmp(a.playerName, "") == 0)
			strcpy_s(a.playerName, 100, "Unknown");
		strcpy_s(b.playerName, 100, "BOT");
	}
	else if (Game::mode == 1) {
		Menu::SetColor(BRIGHT_WHITE, PURPLE);
		Controller::gotoXY(40, 20);
		Menu::printVietnamese(L"Người chơi 1:  ");
		//cout << "PLAYER 1: ";
		cin.getline(a.playerName, 100);
		if (strcmp(a.playerName, "") == 0)
			strcpy_s(a.playerName, 100, "Unknown");
		if (Menu::sound_is_open)
			Controller::playSound(ENTER_SOUND);

		Controller::gotoXY(40, 22);
		Menu::printVietnamese(L"Người chơi 2:  ");
		//cout << "PLAYER 2: ";
		cin.getline(b.playerName, 100);
		if (strcmp(b.playerName, "") == 0)
			strcpy_s(b.playerName, 100, "Unknown");
	}
	if (Menu::sound_is_open)
		Controller::playSound(ENTER_SOUND);
}

void Game::countdown(char last_sign, time_t originalTime, int timeLeft, bool& overTime) {
	time_t nowTime = time(0);
	timeLeft -= (int)difftime(nowTime, originalTime);
	if (timeLeft == 0)
		overTime = true;
	Menu::SetColor(BRIGHT_WHITE, RED);
	if (Game::mode == 0) {
		Controller::gotoXY(69, 9);
		cout << "TIME: " << setw(3) << setfill(' ') << timeLeft << "s";
	}
	else {
		if (last_sign == 'O') {
			Controller::gotoXY(69, 9);
			cout << "TIME: " << setw(3) << setfill(' ') << timeLeft << "s";
			Controller::gotoXY(69, 19);
			cout << "                 ";
		}
		else {
			Controller::gotoXY(69, 19);
			cout << "TIME: " << setw(3) << setfill(' ') << timeLeft << "s";
			Controller::gotoXY(69, 9);
			cout << "                 ";
		}
	}
}