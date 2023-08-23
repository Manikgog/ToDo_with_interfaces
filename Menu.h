#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <conio.h>
#include <string>
#include "IMenu.h"
#include "IInputOutput.h"
#include "InputOutput.h"
#include "IReadWriteFile.h"

/*!
\brief класса Menu служит для обеспечения графического интерфейса с пользователем через различные меню.
Метод MainMenu() обеспечивает основной цикл программы.
Метод PrintOverdueCaseList() выводит на экран дела, у которых вышел срок выполнения.
Метод Draw_menu(const int numAction) отображает основное меню.
Метод input_menu(int low, int hi, int& numAcion) обеспечивает выбор пользователем того или иного пункта всех меню программы.
Метод ChooseCaseMenu(int nCase) отображает меню выбора дела для дальнейшей его обработки или удаления.
Метод ChangeCaseMenu(int numCase, int numAction) отображает меню выбора действий, которые можно выполнить с выбранным в предыдущем меню делом.
Метод MarkCaseMenu() отображает меню для выбора отметки выполнено или не выполнено.
*/
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
	void Variant_Menu(int numCase, int prevCase);
	char input_menu(int low, int hi, volatile int& numAcion);
	int ChooseCaseMenu(int nCase, int prevCase);
	int DrawChooseCaseMenu();
	int DrawChangeCaseMenu(int numCase);
	int ChangeCaseMenu(int numCase, int numAction);
	void DrawMarkCaseMenu();
	int MarkCaseMenu(int numAction, int prevAction);
};

#endif // !_MENU_H_

