#include "InputOutput.h"



InputOutput::InputOutput(const std::string& filename) : _list(filename)
{}

void InputOutput::CursorOff()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	return;
}

void InputOutput::CursorOn()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	return;
}


/*!
\brief метод для обеспечения добавления нового дела в список
*/
void InputOutput::AddingCase()
{
	std::string str_date;							//< string object for entering the date
	Date date;
	std::cout << "\x1b[33mВведите название нового мероприятия -> \x1b[0m";
	std::string title;							//< string object for recording name of the case
	std::getline(std::cin, title);
	do {
		std::cout << "\x1b[33mВведите дату в формате ДД.ММ.ГГГГ -> \x1b[0m";
		std::getline(std::cin, str_date);

	} while (date.CheckDate(str_date) == false);
	Date date_(str_date);
	Case newCase(title, date_, false);
	_list.AddCase(newCase);
	std::cout << "\x1b[32mНовое дело добавлено в список.\x1b[0m\n";

	system("pause");
	system("cls");

}


/*!
\brief метод для изменения названия дела
\param[in] numCase номер дела
*/
void InputOutput::ChangeTitle(int numCase)
{
	std::string answer;
	std::cout << "\x1b[33mВведите новое название дела: \x1b[0m";
	answer = "";

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	
	std::getline(std::cin, answer);
	_list.ChangeTitle(answer, numCase);

	
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

/*!
\brief метод для изменения даты дела
\param[in] numCase номер дела
*/
void InputOutput::ChangeDate(int numCase)
{
	std::string str_date;
	Date date;
	do {
		std::cout << "\x1b[33mВведите дату в формате ДД.ММ.ГГГГ -> \x1b[0m";
		std::getline(std::cin, str_date);
	} while (date.CheckDate(str_date) == false);
	Date date_(str_date);
	_list.ChangeDate(date_, numCase);
}

/*!
\brief метод для удаления дела из списка
\param[in] numCase номер дела
*/
void InputOutput::DeleteCase(int numCase)
{
	std::string answer;
	if (!_list.Size())
	{
		system("cls");
		std::cout << "Cписок дел пуст. Удалять нечего.\n";
		system("pause");
	}
	else {
		std::cout << "\x1b[33mВы уверены, что хотите удалить дело (д/н): \x1b[0m";
		std::cin >> answer;
		if (answer[0] == 'y' || answer[0] == 'д')
		{
			if (_list.DeleteCase(numCase))
				std::cout << "Дело удалено из списка.\n";
			else
				std::cout << "Дело НЕ удалено из списка.\n";
		}
	}
}

/*!
\brief метод для отметки дела как выполненное или нет
\param[in] numCase номер дела
*/
void InputOutput::ChangeMarkCase(int numCase, int mark)
{
	if (mark == 1)
		_list.MarkIsDone(numCase);
	else if(mark == 2)
		_list.MarkIsNotDone(numCase);
	return;
}

/*!
\brief метод возвращает указатель на объект класса CaseList
\param[out] указатель на объект класса CaseList, который является полем InputOutput
*/
CaseList* InputOutput::GetCaseList()
{
	return &_list;
}

