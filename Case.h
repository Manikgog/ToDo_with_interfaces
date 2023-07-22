/*!
\brief Класс Case (задача, дело), который содержит поля название дела и дату
*/
#ifndef _CASE_H_
#define _CASE_H_

#include <string>
#include "Date.h"

class Date;
/*!
\brief класс Case Дело
*/
class Case
{
private:
	std::string _title;		//< _title C++ строка, название дела
	Date _date;				//< _date объект класса Date, дата дела
	bool _isDone;			//< _isDone переменная типа bool, отметка о выполнении: true - дело выполнено, false - невыполнено 
public:
	Case();
	Case(std::string title, std::string date, bool markIsDone);
	Case(std::string title, Date date, bool markIsDone);
	std::string GetTitle();
	Date GetDate();
	void PrintCase(int elLength);
	bool GetIsDoneMark() const;
};

#endif // !_CASE_H_

