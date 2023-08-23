#ifndef _IMENU_H_
#define _IMENU_H_

#include <objbase.h>   // Define interface.

interface IMenu
{
	IMenu() = default;
	virtual ~IMenu() {};
	virtual void MainMenu() = 0;
	virtual void PrintOverdueCaseList() = 0;
	virtual void Draw_menu(const int numAction) = 0;
	virtual char input_menu(int low, int hi, volatile int& numAcion) = 0;
	virtual int ChooseCaseMenu(int nCase, int prevCase) = 0;
	virtual int DrawChooseCaseMenu() = 0;
	virtual int DrawChangeCaseMenu(int numCase) = 0;
	virtual int ChangeCaseMenu(int numCase, int numAction) = 0;
	virtual void DrawMarkCaseMenu() = 0;
	virtual int MarkCaseMenu(int numAction, int prevAction) = 0; 
};

#endif // !_IMENU_H_

