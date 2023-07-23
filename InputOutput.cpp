#include "InputOutput.h"



InputOutput::InputOutput(const std::string& filename) : _list(filename)
{}




/*!
\brief метод для обеспечения добавления нового дела в список
*/
void InputOutput::AddingCase()
{
	std::string date;							//< string object for entering the date

	std::cout << "\x1b[33mВведите название нового мероприятия -> \x1b[0m";
	std::string title;							//< string object for recording name of the case
	std::getline(std::cin, title);
	std::vector<int> vec_date;
	do {
		std::cout << "\x1b[33mВведите дату в формате ДД.ММ.ГГГГ -> \x1b[0m";
		std::getline(std::cin, date);

	} while (CheckDate(date) == false);
	Case newCase(title, date, false);
	_list.AddCase(newCase);
	std::cout << "\x1b[32mНовое дело добавлено в список.\x1b[0m\n";

	system("pause");
	system("cls");

}

/*!
\brief метод для проверки введенной даты
param[in] date дата в виде С++-строки
param[out] возвращает результат в виде булевого значения
*/
bool InputOutput::CheckDate(std::string date)
{
	int arr[3]{};						//< цифра 3 - количество чисел в дате
	std::string s_tmp;
	char c;

	for (size_t i = 0, j = 0; i <= date.length(); ++i)
	{
		if ((date[i] == '.' || i == date.length()) && s_tmp.length() != 0)
		{
			arr[j] = stoi(s_tmp);
			s_tmp.erase();
			j++;
			if (j == 3) break;	//< число 3 - количество чисел в дате т.е. день, месяц, год - три числа
		}

		if (date[i] >= '0' && date[i] <= '9')
		{
			c = date[i];
			s_tmp += c;
		}
	}


	if (IsValidDate(arr[0], arr[1], arr[2]))
		return true;
	return false;

}

/*!
\brief метод для проверки введенной даты
Переданная величина номера дня должна лежать в пределах размеров
переданного месяца. Номер месяца проверяется на соответстви количеству месяцев
в году.
param[in] day номер дня
param[in] month номер месяца
param[in] year год
param[out] возвращает результат в виде булевого значения
*/
bool InputOutput::IsValidDate(int day, int month, int year)
{
	// current date/time based on current system
	time_t now = time(0);

	//std::cout << "Number of sec since January 1,1970:" << now << std::endl;

	tm* ltm = localtime(&now);

	// print various components of tm structure.
	unsigned short currentYear = 1900 + ltm->tm_year;
	unsigned short currentMonth = 1 + ltm->tm_mon;
	unsigned short currentDay = ltm->tm_mday;
	unsigned short lengthOfFeb = 28; // начальная длина февраля / initial length of february
	switch (month) {
	case 1:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 2:
		if (isLeapYear(year))
			lengthOfFeb = 29;
		if (day < 1 || day > lengthOfFeb) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 3:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 4:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 5:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 6:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 7:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 8:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 9:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 10:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 11:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 12:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	}

	if (month > 12) {
		std::cout << "\x1b[31mМесяцев должно быть меньше 13.\x1b[0m" << std::endl;
		return false;
	}

	if (!CheckOverdueCase(day, month, year, currentYear, currentMonth, currentDay))
		return false;

	return true;
}

/*!
\brief метод для проверки високосности года
param[in] year номер года
param[out] true - високосный, false - невисокосный
*/
bool InputOutput::isLeapYear(int year) {
	if (year % 4 == 0) {
		if ((year % 100) == 0 && (year % 400) == 0) {
			//std::cout << "Год " << year << " високосный.\n";
			return true;
		}
		else if ((year % 100) != 0) {
			// std::cout << "Год " << year << " високосный.\n";
			return true;
		}
		else {
			//std::cout << "Год " << year << " не является високосным.\n";
			return false;
		}
	}

	//std::cout << "Год " << year << " не является високосным.\n";
	return false;
}

/*!
\brief метод для проверки прошла ли введённая дата или нет
param[in] day - введённый пользователем день
param[in] month - введённый пользователем месяц
param[in] year - введённый пользователем год
param[in] currentDay - текущий день
param[in] currentMonth - текущий месяц
param[in] currentYear - текущий год
param[out] true - дата не прошла, false - дата уже прошла
*/
bool InputOutput::CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const
{
	if (year < currentYear) {
		std::cout << "\x1b[31mПланируемый год уже прошёл.\x1b[0m" << std::endl;
		return false;
	}
	else if (month < currentMonth && year == currentYear) {
		std::cout << "\x1b[31mПланируемый месяц уже прошёл.\x1b[0m" << std::endl;
		return false;
	}
	else if (day < currentDay && month == currentMonth) {
		std::cout << "\x1b[31mПланируемый день уже прошёл.\x1b[0m" << std::endl;
		return false;
	}
	return true;
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
	std::getline(std::cin, answer);
	_list.ChangeTitle(answer, numCase);
}

/*!
\brief метод для изменения даты дела
\param[in] numCase номер дела
*/
void InputOutput::ChangeDate(int numCase)
{
	std::string date;
	do {
		std::cout << "\x1b[33mВведите дату в формате ДД.ММ.ГГГГ -> \x1b[0m";
		std::getline(std::cin, date);
	} while (CheckDate(date) == false);
	_list.ChangeDate(date, numCase);
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

