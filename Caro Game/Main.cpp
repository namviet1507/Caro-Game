#include "Struct.h"
#include "Controller.h"
int main() {
	Controller::setUpConsole();
	Menu::music_is_open = true;
	Menu::sound_is_open = true;
	Menu::printMainScreen();
	system("PAUSE");
	return 0;
}