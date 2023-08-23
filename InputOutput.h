#ifndef _INPUTOUTPUT_H_
#define _INPUTOUTPUT_H_

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include "Case.h"
#include "Date.h"
#include "CaseList.h"
#include "IInputOutput.h"
#include "IReadWriteFile.h"

/*!
\brief класс, обеспечивает интерфейс с пользователем приложения
Класс выполняет:
- добавление нового дела;
- сортировку списка по дате;
- выбор дела и его изменение или удаление.
*/
class InputOutput : public IinputOutput
{
public:
	InputOutput(const std::string& filename);
	void AddingCase();
	void ChangeTitle(int numCase);
	void ChangeDate(int numCase);
	void DeleteCase(int numCase);
	void ChangeMarkCase(int numCase, int mark);
	CaseList* GetCaseList();
	
private:
	CaseList _list;						//> класс CaseList для хранения и выполнения манипуляций со списком дел
	void CursorOn();
	void CursorOff();

};


#endif // !

