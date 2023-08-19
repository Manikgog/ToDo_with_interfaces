/*!
Класс CaseList обеспечивает:
- хранение списка дел в векторе _caseList
- хранение указателя на объект класса для чтения/записи списка дел в файл _p_IReadWriteBinaryFile
- хранение имени файла _filename
- определение длины максимальной строчки названия дела (size_t MaxLength())
- добавление дела (void AddCase(const Case& case_))
- удаление дела (bool DeleteCase(size_t index))
- определение количества дела в списке (size_t Size() const)
- сортировку списка по дате (void SortCaseListByDate())
- вывод на экран списка дел (void PrintCaseList())
- изменение название существующего дела (void ChangeTitle(const std::string& title, size_t index))
- изменение даты существующего дела (void ChangeDate(const std::string& title, size_t index))
- постановку отметки "выполнено" и "не выполнено" (void MarkIsDone(size_t index) и void MarkIsNotDone(size_t index))
- очистка всего списка дел (void Clear())
*/
#ifndef _CASELIST_H_
#define _CASELIST_H_

#include "Case.h"
#include "Date.h"
#include "IReadWriteFile.h"
#include <vector>
#include <memory>
#include <algorithm>

/*!
\brief класс CaseList Список дел
*/
class CaseList
{
private:
	IReadWriteBinaryFile* _p_IReadWriteBinaryFile = nullptr;	//> указатель на объект класса ReadWriteBinaryFile
	std::vector<std::unique_ptr<Case>> _caseList;				//> вектор с умными указателями на экземпляры класса Case
	const std::string _filename;								//> путь к файлу для хранения списка дел
	static const int _sizeTitle = 56;							//> максимальная длина названия дела
	size_t MaxLength();

public:
	CaseList(const std::string& filename);
	~CaseList();
	void AddCase(const Case& case_);
	bool DeleteCase(size_t index);
	size_t Size() const;
	void SortCaseListByDate();
	size_t GetNumberOfSpaces(size_t index);
	void PrintCaseList();
	void ChangeTitle(const std::string& title, size_t index);
	void ChangeDate(const Date& title, size_t index);
	void MarkIsDone(size_t index);
	void MarkIsNotDone(size_t index);
	Case* GetCase(size_t index) const;
	void Clear();
};

#endif