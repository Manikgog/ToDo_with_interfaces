#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "IMenu.h"
#include "Menu.h"

int main() {
	system("chcp 1251");
	system("cls");

	IMenu* p_IMenu = static_cast<Menu*>(new Menu("case.bin"));

	p_IMenu->MainMenu();

	delete p_IMenu;
	return 0;
}
