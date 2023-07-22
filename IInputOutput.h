#ifndef _IINPUTOUTPUT_H_
#define _IINPUTOUTPUT_H_

#include <string>
#include <objbase.h>   // Define interface.
#include "CaseList.h"

interface IinputOutput
{
	IinputOutput() = default;
	virtual ~IinputOutput() {};
	virtual void AddingCase() = 0;
	virtual bool CheckDate(std::string date) = 0;
	virtual bool IsValidDate(int day, int month, int year) = 0;
	virtual bool isLeapYear(int year) = 0;
	virtual bool CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const = 0;
	virtual void ChangeTitle(int numCase) = 0;
	virtual void ChangeDate(int numCase) = 0;
	virtual void DeleteCase(int numCase) = 0;
	virtual void ChangeMarkCase(int numCase, int mark) = 0;
	virtual CaseList* GetCaseList() = 0;
	
};

#endif // !_IINPUTOUTPUT_H_
