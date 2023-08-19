#include "Case.h"


Case::Case()
	: _title(""), _date(Date()), _isDone(false){}

Case::Case(std::string title, std::string date, bool markIsDone)
	: _title(title), _date(Date(date)), _isDone(markIsDone) {}

Case::Case(std::string title, Date date, bool markIsDone) : _title(title), _date(Date(date)), _isDone(markIsDone) {}

/*!
\brief метод возвращающий С++ строку
\param[out] std::string название дела
*/
std::string Case::GetTitle()
{
	return _title;
}

/*!
\brief метод возвращающий объект класса Date
\param[out] Date
*/
Date Case::GetDate()
{
	return _date;
}

/*!
\brief метод вывода на экран дела
\param[in] elLength количество пробелов для выравнивания
*/
void Case::PrintCase(size_t elLength)
{
	std::cout << _title;
	while (elLength-- > 0)
		std::cout << ' ';				// выравнивание дат с помощью пробелов по длине самой длинной задачи
	std::cout << ' ';
	_date.PrintDate();
	if (_isDone)
		std::cout << "выполнено";
	else
		std::cout << "не выполнено";
}

/*!
\brief метод возвращающий отметку
\param[out] true - дело выполнено, false - невыполнено
*/
bool Case::GetIsDoneMark() const
{
	return _isDone;
}

