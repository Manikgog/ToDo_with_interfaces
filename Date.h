/*!
\brief Класс Date, который содержит поля день, месяц, год
*/
#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>
#include <chrono>
#pragma warning(disable : 4996)



class Date
{
private:
	int _day;
	int _month;
	int _year;
	std::string NumberToString(int month);
public:
	Date();
	Date(int day, int month, int year);
	Date(std::string date);
	int GetDay();
	int GetMonth();
	int GetYear();
	bool operator<(const Date& date);
	bool operator==(const Date& date);
	bool operator>(const Date& date);
	void PrintDate();
};

#endif