#include <memory>
#include <Windows.h>
#include "Menu.h"

void Col(int bg, int txt)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | txt));
}

void setcur(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hConsole, coord);
}

Menu::Menu(const std::string filename) : IMenu()
{
	p_IO = new InputOutput(filename);	//> указатель на объект класса InputOutput
}

Menu::~Menu()
{
	delete p_IO;
}


/*!
\brief метод обеспечивающий текстовый интерфейс с пользователем
*/
void Menu::MainMenu()
{
	bool exit = true;		//< exit - variable-flag for exiting the program / переменна¤-флаг дл¤ выхода из программы
	volatile size_t numAction = 0;	//< numAction - variable for storing an action option from the menu selected by the user
	std::cout << "\x1b[32mПрограмма дл¤ создания списка запланированных дел.\x1b[0m\n";
	if (!p_IO->GetCaseList()->Size())
	{
		PrintOverdueCaseList();
		system("pause");
	}
	char answer{ 'н' };
	do {
		system("cls");
		std::cout << "\x1b[32mПрограмма дл¤ создания списка запланированных дел.\x1b[0m\n";
		Draw_menu(numAction);
		int prevAction = numAction;
		do {
			Variant_Menu(numAction, prevAction);
			prevAction = numAction;
			
		} while (input_menu(1, 5, numAction) != '\r');

		volatile size_t nCase = 0;			//<  nCase - variable for storing the number of the selected case / переменна¤ дл¤ хранени¤ номера выбранного дела
		int nAction = 0;			//< nAction - variable for storing the action number on the selected case / переменная для хранения номера действия над выбранным делом
		switch (numAction) {

		case 1:
			system("cls");
			p_IO->AddingCase();//< AddingCase() - adding a case to the list / добавление дела в список

			break;
		case 2:
			do {
				system("cls");
				DrawChooseCaseMenu();
				nCase = 0;
				int prevCase = nCase;
				do {
					if (1 == ChooseCaseMenu(nCase, prevCase)) { //< если список пуст
						numAction = 1;
						break;
					}
					prevCase = nCase;
				} while ('\r' != input_menu(0, p_IO->GetCaseList()->Size(), nCase));

				system("cls");

				//< exit to the main menu when selecting "Назад"
				//< выход в главное меню при выборе пункта "Назад"
				if (nCase < 0 || nCase >= p_IO->GetCaseList()->Size()) {
					numAction = 1;
					break;
				}
				//< choosing an action with a selected case
				//< выбор действи¤ с выбранным делом
				DrawChangeCaseMenu(nCase);
				do {
					ChangeCaseMenu(numAction, prevAction);
					prevAction = numAction;
				} while (input_menu(1, 5, numAction) != '\r');
				system("cls");
				if (numAction == 1)
				{
					p_IO->ChangeTitle(nCase);
				}
				else if (numAction == 2)
				{
					p_IO->ChangeDate(nCase);
				}
				else if (numAction == 3)
				{
					p_IO->DeleteCase(nCase);
				}
				else if (numAction == 4)
				{
					p_IO->ChangeMarkCase(nCase, this->MarkCaseMenu());
				}
				
					
				//system("pause");
			} while (nAction == 1);

			system("cls");
			break;
		case 3:
			//< clearing the entire list
			//< очистка всего списка
			system("cls");
			Col(0, 15);
			std::cout << "Вы уверены, что хотите удалить все задачи (д/н)? ";
			std::cin >> answer;
			if (answer == 'д' || answer == 'y')
			{
				p_IO->GetCaseList()->Clear();
				if (!p_IO->GetCaseList()->Size())
					std::cout << "Список дел очищен!\n";
			}
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			//< return to the main menu with an empty todo list
			//< возврат в главное меню при пустом списке дел
			if (!p_IO->GetCaseList()->Size()) {
				numAction = 1;
				break;
			}
			Col(0, 15);
			p_IO->GetCaseList()->SortCaseListByDate();
			p_IO->GetCaseList()->PrintCaseList();
			system("pause");
			system("cls");
			break;
		case 5:
			exit = false;
			break;
		}
	} while (exit);
}



/*!
\brief метод для вывода на экран списка просроченных дел
*/
void Menu::PrintOverdueCaseList()
{
	if (!p_IO->GetCaseList()->Size())	// при пустом списке выходим из функции
		return;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	unsigned short currentYear = 1900 + ltm->tm_year;
	unsigned short currentMonth = 1 + ltm->tm_mon;
	unsigned short currentDay = ltm->tm_mday;
	bool is_first = true;
	for (size_t i = 0; i < p_IO->GetCaseList()->Size(); i++)
	{
		if (p_IO->GetCaseList()->GetCase(i)->GetDate() < Date(currentDay, currentMonth, currentYear) && p_IO->GetCaseList()->GetCase(i)->GetIsDoneMark() == false)
		{
			if (is_first)
				std::cout << "\x1b[33mСписок просроченных задач : \x1b[0m\n";
			is_first = false;
			p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
			std::cout << std::endl;
		}
	}
	return;
}



/*!
\brief метод для вывода на экран списка просроченных дел
param[in] numAction целочисленная переменная для подстветки номера действия в меню
*/
void Menu::Draw_menu(const int numAction) {
	Col(0, 15);
	setcur(0, 2); std::cout << "Варианты действий:";
	setcur(0, 3); std::cout << "Добавление нового дела.";
	setcur(0, 4); std::cout << "Выбор дела.";
	setcur(0, 5); std::cout << "Очистка всего списка дел.";
	setcur(0, 6); std::cout << "Сортировка списка.";
	setcur(0, 7); std::cout << "Выход из программы.";
	setcur(0, 8); std::cout << "Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.";
	return;
}

void Menu::Variant_Menu(int numCase, int prevCase)
{
	if (prevCase == 1)
	{
		Col(0, 15);
		setcur(0, prevCase + 2); std::cout << "Добавление нового дела.";
	}
	else if (prevCase == 2)
	{
		Col(0, 15);
		setcur(0, prevCase + 2); std::cout << "Выбор дела.";
	}
	else if (prevCase == 3)
	{
		Col(0, 15);
		setcur(0, prevCase + 2); std::cout << "Очистка всего списка дел.";
	}
	else if (prevCase == 4)
	{
		Col(0, 15);
		setcur(0, prevCase + 2); std::cout << "Сортировка списка.";
	}
	else if (prevCase == 5)
	{
		Col(0, 15);
		setcur(0, prevCase + 2); std::cout << "Выход из программы.";
	}

	if (numCase == 1)
	{
		Col(0, 9);
		setcur(0, numCase + 2); std::cout << "Добавление нового дела.";
	}
	else if (numCase == 2)
	{
		Col(0, 9);
		setcur(0, numCase + 2); std::cout << "Выбор дела.";
	}
	else if (numCase == 3)
	{
		Col(0, 9);
		setcur(0, numCase + 2); std::cout << "Очистка всего списка дел.";
	}
	else if (numCase == 4)
	{
		Col(0, 9);
		setcur(0, numCase + 2); std::cout << "Сортировка списка.";
	}
	else if (numCase == 5)
	{
		Col(0, 9);
		setcur(0, numCase + 2); std::cout << "Выход из программы.";
	}
	
}

/*!
\brief метод для преобразования нажатия на кнопки вверх и вниз в целочисленное значение типа char для последующей обработки
param[in] low нижняя граница номера меню
param[in] hi верхняя граница номера меню
param[in] numAction текущий номер действия в меню
param[out] возвращает результат в виде значения типа char
*/
char Menu::input_menu(int low, int hi, volatile size_t& numAcion) {
	int c1 = 0;
	int c2 = 0;
	int c = c1 + c2;
	do {
		bool f = false;
		if (_kbhit()) {
			c1 = _getch();
			if (c1 == 13) {
				f = true;
				break;
			}
			c2 = _getch();
			c = c1 + c2;
			switch (c) {
			case 296:
				--numAcion;
				break;
			case 304:
				++numAcion;
				break;
			}
		}

	} while (c1 != 13 && c != 296 && c != 304);
	if (numAcion < low)
		numAcion = hi;
	else if (numAcion > hi)
		numAcion = low;
	return (char)c1;
}


/*!
\brief метод для вывода на экран меню выбора дела подсветкой одного из пунктов
param[in] nCase номер дела, которое будет подсвечено
param[out] если возвращается 1, то это сигнал для вызвавшей функции вернуться в предыдущее меню, т.к. список дел пуст
			если же возвращается 0, то продолжается выбор дела
*/
int Menu::ChooseCaseMenu(int nCase, int prevCase)
{
	size_t listSize = p_IO->GetCaseList()->Size();
	if (listSize == 0) {
		Col(0, 11);
		setcur(0, 0); std::cout << "Запланированных дел нет. Список пуст.";
		return 1;
	}
	else
	{
		Col(0, 11);
		setcur(0, 0); std::cout << "Список запланированных дел:";
		if (nCase >= 0 && nCase < listSize) {
			for (int i = 0; i < listSize; ++i) {
				if (nCase == prevCase)
				{
					if (nCase == i)
					{
						Col(0, 9);
						setcur(0, nCase + 1);
						p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
					}
					continue;
				}
				if (nCase == i)
				{
					Col(0, 9);
					setcur(0, nCase + 1);
					p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
				}
				if (prevCase == i)
				{
					Col(0, 15);
					setcur(0, prevCase + 1);
					p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
				}
				std::cout << std::endl;
			}
			Col(0, 15);
			setcur(0, listSize + 1); std::cout << "Назад\n";

		}
		if (nCase == listSize)
		{
			Col(0, 15);
			setcur(0, listSize);
			p_IO->GetCaseList()->GetCase(listSize-1)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(listSize - 1));
			Col(0, 9);
			setcur(0, listSize + 1); std::cout << "Назад\n";
		}
	}
	return 0;
}


int Menu::DrawChooseCaseMenu()
{
	size_t listSize = p_IO->GetCaseList()->Size();
	if (listSize == 0) {
		Col(0, 11);
		setcur(0, 0); std::cout << "Запланированных дел нет. Список пуст.";
		return 1;
	}
	else
	{
		Col(0, 11);
		setcur(0, 0); std::cout << "Список запланированных дел:";
		
		for (int i = 0; i < listSize; ++i) {
			Col(0, 15);
			setcur(0, i + 1);
			p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
			std::cout << std::endl;
		}
		std::cout << "Назад\n";
		
		
	}
	return 0;
}

int Menu::DrawChangeCaseMenu(int numCase)
{
	if (numCase < 0) numCase = 0;
	system("cls");
	Col(0, 15);
	setcur(0, 0);
	p_IO->GetCaseList()->GetCase(numCase)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(numCase));

	Col(0, 15);
	setcur(0, 1); std::cout << "Изменить название";
	setcur(0, 2); std::cout << "Изменить дату";
	setcur(0, 3); std::cout << "Удалить дело";
	setcur(0, 4); std::cout << "Поставить отметку";
	setcur(0, 5); std::cout << "Назад";
}


/*!
\brief метод для отображения меню выбора действия для изменения или удаления дела
\param[in] numCase номер дела
\param[out] номер пункта меню
*/
int Menu::ChangeCaseMenu(volatile int numAction, int prevAction)
{
			
	if (prevAction == 1)
	{
		Col(0, 15);
		setcur(0, prevAction); std::cout << "Изменить название";
	}
	else if (prevAction == 2)
	{
		Col(0, 15);
		setcur(0, prevAction); std::cout << "Изменить дату";
	}
	else if (prevAction == 3)
	{
		Col(0, 15);
		setcur(0, prevAction); std::cout << "Удалить дело";
	}
	else if (prevAction == 4)
	{
		Col(0, 15);
		setcur(0, prevAction); std::cout << "Поставить отметку";
	}
	else if (prevAction == 5)
	{
		Col(0, 15);
		setcur(0, prevAction); std::cout << "Назад\n";
	}

	if (numAction == 1)
	{
		Col(0, 9);
		setcur(0, numAction); std::cout << "Изменить название";
	}
	else if (numAction == 2)
	{
		Col(0, 9);
		setcur(0, numAction); std::cout << "Изменить дату";
	}
	else if (numAction == 3)
	{
		Col(0, 9);
		setcur(0, numAction); std::cout << "Удалить дело";
	}
	else if (numAction == 4)
	{
		Col(0, 9);
		setcur(0, numAction); std::cout << "Поставить отметку";
	}
	else if (numAction == 5)
	{
		Col(0, 9);
		setcur(0, numAction); std::cout << "Назад\n";
	}
	return 0;
}

/*!
метод для отметки дела как выполненное или нет
\param[in] numCase номер дела
*/
int Menu::MarkCaseMenu()
{
	size_t num = 3;
	do {
		switch (num)
		{
		case 1:
			system("cls");
			std::cout << "Выберите отметку:\n";
			std::cout << "\x1b[36mВыполнено\x1b[0m\n";
			std::cout << "Не выполнено\n";
			std::cout << "Назад\n";
			break;
		case 2:
			system("cls");
			std::cout << "Выберите отметку:\n";
			std::cout << "Выполнено\n";
			std::cout << "\x1b[36mНе выполнено\x1b[0m\n";
			std::cout << "Назад\n";
			break;
		case 3:
			system("cls");
			std::cout << "Выберите отметку:\n";
			std::cout << "Выполнено\n";
			std::cout << "Не выполнено\n";
			std::cout << "\x1b[36mНазад\x1b[0m\n";
			break;
		}
	} while (input_menu(1, 3, num) != '\r');

	return num;
}