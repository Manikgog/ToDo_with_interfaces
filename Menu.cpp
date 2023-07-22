#include <memory>
#include "Menu.h"

Menu::Menu(const std::string filename) : IMenu()
{
	p_IO = static_cast<InputOutput*>(new InputOutput(filename));	//> указатель на объект класса InputOutput
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
	bool exit = true;	//< bool exit - variable-flag for exiting the program / переменна¤-флаг дл¤ выхода из программы
	int numAction = 0;	//< int numAction - variable for storing an action option from the menu selected by the user
	
	char answer{ 'н' };
	do {


		do {
			system("cls");
			std::cout << "\x1b[32mПрограмма дл¤ создания списка запланированных дел.\x1b[0m\n";
			PrintOverdueCaseList();

			Draw_menu(numAction);
		} while (input_menu(1, 5, numAction) != '\r');

		int nCase = 0;				//< int nCase - variable for storing the number of the selected case / переменна¤ дл¤ хранени¤ номера выбранного дела
		int nAction = 0;			//< int nAction - variable for storing the action number on the selected case / переменная для хранения номера действия над выбранным делом
		switch (numAction) {

		case 1:
			
			p_IO->AddingCase();//< AddingCase() - adding a case to the list / добавление дела в список

			break;
		case 2:
			do {
				do {
					system("cls");
					if (1 == ChooseCaseMenu(nCase)) { //< если список пуст
						numAction = 1;
						break;
					}
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
				numAction = ChangeCaseMenu(nCase, numAction);
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
				
					
				system("pause");
			} while (nAction == 1);

			system("cls");
			break;
		case 3:
			//< clearing the entire list
			//< очистка всего списка
			system("cls");

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
}



/*!
\brief метод для вывода на экран списка просроченных дел
param[in] numAction целочисленная переменная для подстветки номера действия в меню
*/
void Menu::Draw_menu(const int numAction) {
	switch (numAction) {

	case 1:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\n\x1b[36mДобавление нового дела.\x1b[0m\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 2:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
\x1b[36mВыбор дела.\x1b[0m\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 3:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
\x1b[36mОчистка всего списка дел.\x1b[0m\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 4:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
\x1b[36mСортировка списка.\x1b[0m\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 5:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
\x1b[36mВыход из программы.\x1b[0m\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	default:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
	}
}

/*!
\brief метод для преобразования нажатия на кнопки вверх и вниз в целочисленное значение типа char для последующей обработки
param[in] low нижняя граница номера меню
param[in] hi верхняя граница номера меню
param[in] numAction текущий номер действия в меню
param[out] возвращает результат в виде значения типа char
*/
char Menu::input_menu(int low, int hi, int& numAcion) {
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
int Menu::ChooseCaseMenu(int nCase)
{
	size_t listSize = p_IO->GetCaseList()->Size();
	if (listSize == 0) {
		std::cout << "Запланированных дел нет. Список пуст.\n";
		return 1;
	}
	else {


		std::cout << "\x1b[33mСписок запланированных дел:\x1b[0m\n";
		if (nCase >= 0 && nCase < listSize) {
			for (int i = 0; i < listSize; ++i) {
				if (nCase == i)
				{
					std::cout << "\x1b[36m";
					p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
					std::cout << "\x1b[0m";
				}
				else
					p_IO->GetCaseList()->GetCase(i)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(i));
				std::cout << std::endl;
			}
			std::cout << "Назад\n";
		}
		else {
			p_IO->GetCaseList()->PrintCaseList();
			std::cout << "\x1b[36mНазад\x1b[0m\n";
		}
	}
	return 0;
}




/*!
\brief метод для отображения меню выбора действия для изменения или удаления дела
\param[in] numCase номер дела
\param[out] номер пункта меню
*/
int Menu::ChangeCaseMenu(int numCase, int numAction)
{
	if (numCase < 0) numCase = 0;
	int num = 1;
	do {

		switch (num)
		{
		case 1:
			system("cls");
			p_IO->GetCaseList()->GetCase(numCase)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(numCase));
			std::cout << "\n\x1b[36mИзменить название\x1b[0m\n";
			std::cout << "Изменить дату\n";
			std::cout << "Удалить дело\n";
			std::cout << "Поставить отметку\n";
			std::cout << "Назад\n";
			break;
		case 2:
			system("cls");
			p_IO->GetCaseList()->GetCase(numCase)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "\x1b[36mИзменить дату\x1b[0m\n";
			std::cout << "Удалить дело\n";
			std::cout << "Поставить отметку\n";
			std::cout << "Назад\n";
			break;
		case 3:
			system("cls");
			p_IO->GetCaseList()->GetCase(numCase)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "Изменить дату\n";
			std::cout << "\x1b[36mУдалить дело\x1b[0m\n";
			std::cout << "Поставить отметку\n";
			std::cout << "Назад\n";
			break;
		case 4:
			system("cls");
			p_IO->GetCaseList()->GetCase(numCase)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "Изменить дату\n";
			std::cout << "Удалить дело\n";
			std::cout << "\x1b[36mПоставить отметку\x1b[0m\n";
			std::cout << "Назад\n";
			break;
		case 5:
			system("cls");
			p_IO->GetCaseList()->GetCase(numCase)->PrintCase(p_IO->GetCaseList()->GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "Изменить дату\n";
			std::cout << "Удалить дело\n";
			std::cout << "Поставить отметку\n";
			std::cout << "\x1b[36mНазад\x1b[0m\n";
			break;
		default:
			break;
		}
	} while (input_menu(1, 5, num) != '\r');
	return num;
}

/*!
метод для отметки дела как выполненное или нет
\param[in] numCase номер дела
*/
int Menu::MarkCaseMenu()
{
	int num = 3;
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