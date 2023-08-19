#include <iostream>
#include <locale>
#include <Windows.h>
#include <ctime>

#include "IMenu.h"
#include "Menu.h"

int main() {
	system("chcp 1251");
	system("cls");

	IMenu* p_IMenu = new Menu("case.bin");

	p_IMenu->MainMenu();

	delete p_IMenu;
	return 0;
}
