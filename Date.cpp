#include "Date.h"
#include "InputOutput.h"


/*!
\brief метод для проверки високосности года
param[in] year номер года
param[out] true - високосный, false - невисокосный
*/
bool Date::isLeapYear(int year) {
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
\brief метод для проверки введенной даты
Переданная величина номера дня должна лежать в пределах размеров
переданного месяца. Номер месяца проверяется на соответстви количеству месяцев
в году.
param[in] day номер дня
param[in] month номер месяца
param[in] year год
param[out] возвращает результат в виде булевого значения
*/
bool Date::IsValidDate(int day, int month, int year)
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
\brief метод преобразующий номер месяца в название в виде С++ строки
\param[in] month номер месяца
\param[out] C++ cтрока названия месяца
*/
std::string Date::NumberToString(int month)
{
	std::string month_str;
	switch (month) {
	case 1:
		month_str = "января";
		break;
	case 2:
		month_str = "февраля";
		break;
	case 3:
		month_str = "марта";
		break;
	case 4:
		month_str = "апреля";
		break;
	case 5:
		month_str = "мая";
		break;
	case 6:
		month_str = "июня";
		break;
	case 7:
		month_str = "июля";
		break;
	case 8:
		month_str = "августа";
		break;
	case 9:
		month_str = "сентября";
		break;
	case 10:
		month_str = "октября";
		break;
	case 11:
		month_str = "ноября";
		break;
	case 12:
		month_str = "декабря";
		break;
	}
	return month_str;
}

Date::Date() : _day(1), _month(1), _year(1970) {}

Date::Date(int day, int month, int year)
	: _day(day), _month(month), _year(year)
{}

/*!
\brief конструктор, преобразующий С++ строку в дату _day, _month, _year
*/
Date::Date(std::string date)
{
	int arr[3]{};
	std::string s_tmp;
	char c;

	for (size_t i = 0, j = 0; i <= date.length(); ++i)
	{
		if ((date[i] == '.' || i == date.length()) && s_tmp.length() != 0)
		{
			arr[j] = stoi(s_tmp);
			s_tmp.erase();
			j++;
			if (j == 3) break;
		}

		if (date[i] >= '0' && date[i] <= '9')
		{
			c = date[i];
			s_tmp += c;
		}
	}
	_day = arr[0];
	_month = arr[1];
	_year = arr[2];
}


/*!
\brief метод возвращающий дня
\param[out] _day число дня
*/
int Date::GetDay()
{
	return _day;
}

/*!
\brief метод возвращающий число месяца
\param[out] _month число месяца
*/
int Date::GetMonth()
{
	return _month;
}

/*!
\brief метод возвращающий число года
\param[out] _year число года
*/
int Date::GetYear()
{
	return _year;
}

/*!
\brief перегрузка оператора '<'
\param[out] bool
*/
bool Date::operator<(const Date& date)
{
	if (_year < date._year) {
		//std::cout << "\x1b[31mПланируемый год уже прошёл.\x1b[0m" << std::endl;
		return true;
	}
	else if (_month < date._month && _year == date._year) {
		//std::cout << "\x1b[31mПланируемый месяц уже прошёл.\x1b[0m" << std::endl;
		return true;
	}
	else if (_day < date._day && _month == date._month) {
		//std::cout << "\x1b[31mПланируемый день уже прошёл.\x1b[0m" << std::endl;
		return true;
	}
	return false;
}

/*!
\brief перегрузка оператора '=='
\param[out] bool
*/
bool Date::operator==(const Date& date)
{
	if (_year == date._year && _month == date._month && _day == date._day)
	{
		return true;
	}
	return false;
}

/*!
\brief перегрузка оператора '>'
\param[out] bool
*/
bool Date::operator>(const Date& date)
{
	if ((*this < date) || (*this == date))
		return false;
	return true;
}

/*!
\brief метод для вывода на экран даты
*/
void Date::PrintDate()
{
	std::cout << GetDay();
	if (GetDay() < 10)
		std::cout << ' ';
	std::cout << ' ' << NumberToString(GetMonth());
	int maxLengthOfMonth = 8; //< maxLengthOfMonth сентябрь - самый длинный месяц по количеству букв 
	int numberOfSpaces = maxLengthOfMonth - NumberToString(GetMonth()).size();
	while (numberOfSpaces-- > 0)				// выравнивание пробелами
		std::cout << ' ';
	std::cout << ' ' << GetYear() << ' ';

}

/*!
\brief метод для проверки введенной даты
param[in] date дата в виде С++-строки
param[out] возвращает результат в виде булевого значения
*/
bool Date::CheckDate(std::string date)
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
\brief метод для проверки прошла ли введённая дата или нет
param[in] day - введённый пользователем день
param[in] month - введённый пользователем месяц
param[in] year - введённый пользователем год
param[in] currentDay - текущий день
param[in] currentMonth - текущий месяц
param[in] currentYear - текущий год
param[out] true - дата не прошла, false - дата уже прошла
*/
bool Date::CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const
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
