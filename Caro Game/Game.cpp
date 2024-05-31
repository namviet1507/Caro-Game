#include "Game.h"
#include "Point.h"


Point** Game::board = NULL;
Point* Game::cur_point = NULL;
Point* Game::bot_point = NULL;
stack<Point*> Game::history;

int Game::mode; // 0 là 1 người chơi, 1 là 2 người chơi
int Game::wonp1 = 0;
int Game::wonp2 = 0;
bool Game::isPlayting;
bool Game::XWin;


void Game::setupGame() {
	Game::XWin = false;
	if (Game::mode == 2) {
		Menu::goBack();
	}
	Game::isPlayting = true;
	system("cls");
	system("color F0");
	createBoard();
	cur_point = &board[7][7];
	printBoard();
	printScoreBoard(); // in bảng điểm
	printPoint(cur_point, BLUE, BLACK);
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
				Menu::SetColor(BRIGHT_WHITE, RED);
			else
				Menu::SetColor(BRIGHT_WHITE, BLUE);
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
	int x = 65, y = 0;
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(x, y, 42, 28);

	// player 1
	Menu::printRectangle(x + 2, y + 1, 38, 9);
	Controller::gotoXY(x + 4, y + 4);
	cout << "Player 1";
	Menu::SetColor(BRIGHT_WHITE, RED);
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

	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(x + 4, y + 6);
	cout << "Won: " << wonp1;

	// player 2
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(x + 2, y + 11, 38, 9);
	if (mode == 0) {
		Controller::gotoXY(x + 4, y + 14);
		cout << "Bot";
	}
	else {
		Controller::gotoXY(x + 4, y + 14);
		cout << "Player 2";
	}

	Controller::gotoXY(x, y + 11);
	Menu::SetColor(BRIGHT_WHITE, LIGHT_BLUE);
	cout << R"(
											 ________     
											|\   __  \    
											\ \  \|\  \   
											 \ \  \\\  \  
											  \ \  \\\  \ 
											   \ \_______\
										  	    \|_______|
	)";

	Menu::SetColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(x + 4, y + 16);
	cout << "Won: " << wonp2;




	Menu::printRectangle(x + 3, y + 21, 15, 2);
	Controller::gotoXY(x + 8, y + 22);
	cout << "Q: QUIT";
	Menu::printRectangle(x + 24, y + 21, 15, 2);
	Controller::gotoXY(x + 28, y + 22);
	cout << "L: SAVE";
	Menu::printRectangle(x + 3, y + 24, 15, 2);
	Controller::gotoXY(x + 8, y + 25);
	cout << "H: HELP";
	Menu::printRectangle(x + 24, y + 24, 15, 2);
	Controller::gotoXY(x + 27, y + 25);
	cout << "M: SETTING";


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
	char last_sign = 'O';
	if (Menu::music_is_open)
		Controller::playSound(7);
	while (true) {
		if (cur_point->sign == 'X')
			printPoint(cur_point, YELLOW, BLUE);
		else if (cur_point->sign == 'O')
			printPoint(cur_point, YELLOW, RED);
		else
			printPoint(cur_point, YELLOW, BLACK);

		int key = Controller::getConsoleInput();
		if (Menu::sound_is_open)
			Controller::playSound(MOVE_SOUND);
		switch (key) {
		case 1: // esc
			Menu::SetColor(BLACK, BRIGHT_WHITE);
			system("cls");
			exit(0);
			return;
		case 2: // up
			if (cur_point->row > 0) {
				if (Menu::sound_is_open)
					Controller::playSound(MOVE_SOUND);

				if (cur_point->sign == 'X')
					printPoint(cur_point, BRIGHT_WHITE, BLUE);
				else if (cur_point->sign == 'O')
					printPoint(cur_point, BRIGHT_WHITE, RED);
				else
					printPoint(cur_point, BRIGHT_WHITE, BLACK);

				cur_point = &board[cur_point->row - 1][cur_point->col];
			}
			break;
		case 3: // left
			if (cur_point->col > 0) {
				if (Menu::sound_is_open)
					Controller::playSound(MOVE_SOUND);

				if (cur_point->sign == 'X')
					printPoint(cur_point, BRIGHT_WHITE, BLUE);
				else if (cur_point->sign == 'O')
					printPoint(cur_point, BRIGHT_WHITE, RED);
				else
					printPoint(cur_point, BRIGHT_WHITE, BLACK);

				cur_point--;
			}
			break;
		case 4: // right
			if (cur_point->col < BOARD_SIZE - 1) {
				if (Menu::sound_is_open)
					Controller::playSound(MOVE_SOUND);

				if (cur_point->sign == 'X')
					printPoint(cur_point, BRIGHT_WHITE, BLUE);
				else if (cur_point->sign == 'O')
					printPoint(cur_point, BRIGHT_WHITE, RED);
				else
					printPoint(cur_point, BRIGHT_WHITE, BLACK);

				cur_point++;
			}
			break;
		case 5: // down
			if (cur_point->row < BOARD_SIZE - 1) {
				if (Menu::sound_is_open)
					Controller::playSound(MOVE_SOUND);

				if (cur_point->sign == 'X')
					printPoint(cur_point, BRIGHT_WHITE, BLUE);
				else if (cur_point->sign == 'O')
					printPoint(cur_point, BRIGHT_WHITE, RED);
				else
					printPoint(cur_point, BRIGHT_WHITE, BLACK);

				cur_point = &board[cur_point->row + 1][cur_point->col];
			}
			break;
		case 6:
			if (cur_point->sign == ' ') {
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
							printPoint(cur_point, BRIGHT_WHITE, BLUE);
						else if (cur_point->sign == 'O')
							printPoint(cur_point, BRIGHT_WHITE, RED);
						else
							printPoint(cur_point, BRIGHT_WHITE, BLACK);

						processWinGame(direction_win, cur_point);

						if (cur_point->sign == 'X')
							wonp1++;
						else if (cur_point->sign == 'O')
							wonp2++;

						resetGame();
						break;
					}
				}
				else if (Game::mode == 0) {
					// 1 người chơi
					cur_point->sign = 'X';

					history.push(cur_point);

					if (cur_point->sign == 'X')
						printPoint(cur_point, BRIGHT_WHITE, BLUE);
					else if (cur_point->sign == 'O')
						printPoint(cur_point, BRIGHT_WHITE, RED);
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
							printPoint(cur_point, BRIGHT_WHITE, BLUE);
						else if (cur_point->sign == 'O')
							printPoint(cur_point, BRIGHT_WHITE, RED);
						else
							printPoint(cur_point, BRIGHT_WHITE, BLACK);

						if (cur_point->sign == 'X')
							printPoint(cur_point, BRIGHT_WHITE, BLUE);
						else if (cur_point->sign == 'O')
							printPoint(cur_point, BRIGHT_WHITE, RED);
						else
							printPoint(cur_point, BRIGHT_WHITE, BLACK);

						processWinGame(direction_win, cur_point);

						wonp1++;

						resetGame();
						break;
					}

					// lượt của bot
					processBot();

					bot_point->sign = 'O';

					history.push(bot_point);

					if (bot_point->sign == 'X')
						printPoint(bot_point, BRIGHT_WHITE, BLUE);
					else if (bot_point->sign == 'O')
						printPoint(bot_point, BRIGHT_WHITE, RED);
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
							printPoint(bot_point, BRIGHT_WHITE, BLUE);
						else if (bot_point->sign == 'O')
							printPoint(bot_point, BRIGHT_WHITE, RED);
						else
							printPoint(bot_point, BRIGHT_WHITE, BLACK);

						processWinGame(direction_win, bot_point);

						wonp2++;

						resetGame();
						break;
					}
				}
				else {
					if (Menu::sound_is_open)
						Controller::playSound(ERROR_SOUND);
				}


				if (checkDraw()) {
					Controller::gotoXY(80, 15);
					Menu::SetColor(BLACK, WHITE);
					cout << "Draw";

					resetGame();

					Menu::SetColor(BLACK, BRIGHT_WHITE);
					system("cls");
					exit(0);
				}
			}
			break;
		case 7: // Help
			Menu::helpScreen();
			break;
		case 8: // Quit
			Menu::goBack();
			break;
		case 9: // L, l
			processSaveFile(last_sign);
			break;
		case 11: // Setting
			Menu::Setting();
			break;
		default:
			break;
		}
	}
}

void Game::resetGame() {
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	system("cls");
	Game::isPlayting = false;
	if (Game::XWin) {
		Menu::SetColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(0, 3);
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
		Controller::gotoXY(0, 3);
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
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(33, 17, 45, 8);
	Controller::gotoXY(44, 18);
	cout << "DO YOU WANT TO CONTINUE ?";
	int choice[2] = { 0,0 }, curChoice = 0;
	while (true) {
		choice[curChoice] = 1;
		if (choice[0]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(40, 20 + i);
				cout << "           ";
			}
			Controller::gotoXY(44, 21);
			cout << "YES";
		}
		else {
			Controller::gotoXY(40, 21);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "           ";
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Menu::printRectangle(40, 20, 9, 2);
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Controller::gotoXY(44, 21);
			cout << "YES";
		}
		if (choice[1]) {
			Menu::SetColor(GREEN, BRIGHT_WHITE);
			for (int i = 0; i < 3; i++) {
				Controller::gotoXY(62, 20 + i);
				cout << "           ";
			}
			Controller::gotoXY(66, 21);
			cout << "NO";
		}
		else {
			Controller::gotoXY(62, 21);
			Menu::SetColor(BRIGHT_WHITE, BRIGHT_WHITE);
			cout << "           ";
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Menu::printRectangle(62, 20, 9, 2);
			Menu::SetColor(BRIGHT_WHITE, PURPLE);
			Controller::gotoXY(66, 21);
			cout << "NO";
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

//bool Game::defBot() {
//	Point* point = cur_point;
//	char sign = point->sign;
//	int count = 0;
//	int max = 0;
//
//	// theo chiều dọc
//	while (point->sign == sign) {
//		if (point->row == 0) break;
//		point = &board[point->row - 1][point->col];
//	}
//
//	if (point->sign == ' ') {
//		bot_point = point;
//		count++;
//	}
//
//	point = &board[point->row + 1][point->col];
//
//	while (point->sign == sign) {
//		if (point->row == BOARD_SIZE - 1) break;
//		point = &board[point->row + 1][point->col];
//		count++;
//	}
//
//	if (count >= 3 && point->sign == ' ') {
//		bot_point = point;
//		return true;
//	}
//	else if (count >= 3) return true;
//
//	// theo chiều ngang
//	count = 0;
//	point = cur_point;
//	while (point->sign == sign) {
//		if (point->col == 0) break;
//		point = &board[point->row][point->col - 1];
//	}
//
//	if (point->sign == ' ') {
//		bot_point = point;
//		count++;
//	}
//
//	point = &board[point->row][point->col + 1];
//
//	while (point->sign == sign) {
//		if (point->row == BOARD_SIZE - 1) break;
//		point = &board[point->row][point->col + 1];
//		count++;
//	}
//
//	if (count >= 3 && point->sign == ' ') {
//		bot_point = point;
//		return true;
//	}
//	else if (count >= 3) return true;
//
//	// theo dấu huyền
//	count = 0;
//	point = cur_point;
//	while (point->sign == sign) {
//		if (point->row == 0 || point->col == 0) break;
//		point = &board[point->row - 1][point->col - 1];
//	}
//
//	if (point->sign == ' ') {
//		bot_point = point;
//		count++;
//	}
//
//	point = &board[point->row + 1][point->col + 1];
//
//	while (point->sign == sign) {
//		if (point->row == BOARD_SIZE - 1 || point->col == BOARD_SIZE) break;
//		point = &board[point->row + 1][point->col + 1];
//		count++;
//	}
//
//	if (count >= 3 && point->sign == ' ') {
//		bot_point = point;
//		return true;
//	}
//	else if (count >= 3) return true;
//
//	// theo dấu sắc
//	count = 0;
//	point = cur_point;
//	while (point->sign == sign) {
//		if (point->row == 0 || point->col == BOARD_SIZE - 1) break;
//		point = &board[point->row - 1][point->col + 1];
//	}
//
//	if (point->sign == ' ') {
//		bot_point = point;
//		count++;
//	}
//
//	point = &board[point->row + 1][point->col - 1];
//
//	while (point->sign == sign) {
//		if (point->row == BOARD_SIZE - 1 || point->col == 0) break;
//		point = &board[point->row + 1][point->col - 1];
//		count++;
//	}
//
//	if (count >= 3 && point->sign == ' ') {
//		bot_point = point;
//		return true;
//	}
//	else if (count >= 3) return true;
//
//	return false;
//}
//
//void Game::atkBot() {
//	Point* point = cur_point;
//	if (bot_point == NULL) {
//		if (point->col != BOARD_SIZE - 1)
//			bot_point = &board[point->row][point->col + 1];
//		else
//			bot_point = &board[point->row][point->col - 1];
//
//		return;
//	}
//
//	// theo chiều dọc
//	point = bot_point;
//	char sign = point->sign;
//	while (point->row > 0 && board[point->row - 1][point->col].sign == ' ') {
//		point = &board[point->row - 1][point->col];
//	}
//	if (point->row > 0 && board[point->row - 1][point->col].sign == sign) {
//		bot_point = &board[point->row - 1][point->col];
//		return;
//	}
//
//	// theo chiều ngang
//	point = bot_point;
//	while (point->col > 0 && board[point->row][point->col - 1].sign == ' ') {
//		point = &board[point->row][point->col - 1];
//	}
//	if (point->col > 0 && board[point->row][point->col - 1].sign == sign) {
//		bot_point = &board[point->row][point->col - 1];
//		return;
//	}
//
//	// theo dấu huyền
//	point = bot_point;
//	while (point->row > 0 && point->col > 0 && board[point->row - 1][point->col - 1].sign == ' ') {
//		point = &board[point->row - 1][point->col - 1];
//	}
//	if (point->row > 0 && point->col > 0 && board[point->row - 1][point->col - 1].sign == sign) {
//		bot_point = &board[point->row - 1][point->col - 1];
//		return;
//	}
//
//	// theo dấu sắc
//	point = bot_point;
//	while (point->row > 0 && point->col < BOARD_SIZE - 1 && board[point->row - 1][point->col + 1].sign == ' ') {
//		point = &board[point->row - 1][point->col + 1];
//	}
//	if (point->row > 0 && point->col < BOARD_SIZE - 1 && board[point->row - 1][point->col + 1].sign == sign) {
//		bot_point = &board[point->row - 1][point->col + 1];
//		return;
//	}
//
//	// nếu không tìm thấy nước đi tấn công, chọn nước đi ngẫu nhiên
//	if (bot_point == NULL) {
//		if (point->col != BOARD_SIZE - 1)
//			bot_point = &board[point->row][point->col + 1];
//		else
//			bot_point = &board[point->row][point->col - 1];
//	}
//}

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
	Menu::SetColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(56, 12, 30, 6);

	Controller::gotoXY(57, 13);
	for (int i = 0; i < 5; i++) {
		Controller::gotoXY(57, 13 + i);
		for (int j = 0; j < 29; j++)
			cout << ' ';
	}

	Controller::gotoXY(60, 13);
	cout << "Input your file name";
	Controller::gotoXY(57, 14);
	for (int i = 0; i < 29; i++)
		putchar(196);

	string namefile;
	Controller::gotoXY(58, 15);
	getline(cin, namefile);

	fstream listFile;
	listFile.open(LIST_FILE, ios::app);
	if (!listFile) {
		freeBoard();
		Menu::SetColor(BLACK, BRIGHT_WHITE);
		system("cls");
		exit(0);
		return;
	}
	listFile << namefile << '\n';
	listFile.close();

	namefile = "readLoadGame\\" + namefile + ".txt";

	fstream outFile;
	outFile.open(namefile, ios::out);

	outFile << mode << '\n';
	outFile << BOARD_SIZE << '\n';
	outFile << cur_point->row << ' ' << cur_point->col << '\n';
	outFile << last_sign << '\n';
	outFile << history.size() << '\n';

	while (history.empty() == false) {
		outFile << history.top()->row << ' ' << history.top()->col << ' ' << history.top()->sign << '\n';
		history.pop();
	}


	outFile.close();


	Controller::gotoXY(57, 13);
	cout << "                            ";
	Controller::gotoXY(57, 15);
	cout << "                            ";

	Controller::gotoXY(60, 13);
	cout << "Do you want to continue?";
	Menu::printRectangle(58, 15, 10, 2);
	Controller::gotoXY(60, 16);
	cout << "Y: YES";
	Menu::printRectangle(74, 15, 10, 2);
	Controller::gotoXY(76, 16);
	cout << "N: NO";

	while (true) {
		int key = Controller::getConsoleInput();

		if (key == 10) {
			system("cls");
			printBoard();
			printScoreBoard();
			break;
		}
		else if (key == 12) {
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

	inFile.open(filename, ios::in);

	if (!inFile) return;
	int size, row, col;
	char last_sign, sign;
	inFile >> mode;
	inFile >> size;
	inFile >> row >> col;
	inFile >> last_sign;
	inFile >> size;
	createBoard();
	cur_point = &board[row][col];
	stack<Point*> temp;
	for (int i = 0; i < size; i++) {
		inFile >> row >> col >> sign;
		board[row][col].sign = sign;
		temp.push(&board[row][col]);
	}


	while (temp.empty() == false) {
		history.push(temp.top());
		temp.pop();
	}

	system("cls");
	system("color F0");
	printBoard();
	printScoreBoard(); // in bảng điểm

	if (cur_point->sign == 'X')
		printPoint(cur_point, YELLOW, BLUE);
	else if (cur_point->sign == 'O')
		printPoint(cur_point, YELLOW, RED);
	else
		printPoint(cur_point, YELLOW, BLACK);

	controlPoint();


	inFile.close();
}