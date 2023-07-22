#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <conio.h>
#include <string>
#include "IMenu.h"
#include "IInputOutput.h"
#include "InputOutput.h"
#include "IReadWriteFile.h"

class Menu : public IMenu
{
private:
	IinputOutput* p_IO = nullptr;	
public:
	Menu(const std::string filename);
	~Menu() override;
	void MainMenu();
	void PrintOverdueCaseList();
	void Draw_menu(const int numAction);
	char input_menu(int low, int hi, int& numAcion);
	int ChooseCaseMenu(int nCase);
	int ChangeCaseMenu(int numCase, int numAction);
	int MarkCaseMenu();
};

#endif // !_MENU_H_

