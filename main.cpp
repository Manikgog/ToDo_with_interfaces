#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "IMenu.h"
#include "Menu.h"

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); // установка кодовой страницы на ввод текста
	srand(time(NULL));

	IMenu* p_IMenu = static_cast<Menu*>(new Menu("case.bin"));

	p_IMenu->MainMenu();

	delete p_IMenu;
	return 0;
}
