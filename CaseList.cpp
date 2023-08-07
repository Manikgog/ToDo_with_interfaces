#include <memory>
#include <fstream>
#include "CaseList.h"
#include "ReadWriteFile.h"
#include "Case.h"

/*!
\brief метод для определения самого длинного названия дела
Служит для выравнивания списка дел при выводе на экран
\param[out] длину самого длинного названия дела
*/
size_t CaseList::MaxLength()
{
	size_t maxLength = 0;
	for (const auto& el : this->_caseList)
	{
		if (maxLength < el->GetTitle().size())
			maxLength = el->GetTitle().size();
	}
	return maxLength;
}

/*!
\brief конструктор класса CaseList
Выполняет чтения списка дел из файла
*/
CaseList::CaseList(const std::string& filename)
{
	_p_IReadWriteBinaryFile = static_cast<IReadWriteBinaryFile*>(new ReadWriteBinaryFile(filename));
	this->_caseList = _p_IReadWriteBinaryFile->ReadBinaryFile();
	
}

/*!
\brief деструктор класса CaseList
Выполняет запись списка дел в файл
*/
CaseList::~CaseList()
{
	_p_IReadWriteBinaryFile->WriteBinaryFile(this->_caseList);
	delete _p_IReadWriteBinaryFile;
}

/*!
\brief метод для добавления дела в конец списка
param[in] case_ ссылка на объект класса Case
*/
void CaseList::AddCase(const Case& case_)
{
	this->_caseList.push_back(std::make_unique<Case>(case_));
}

/*!
\brief метод для удаления дела по индексу
param[in] index индекс дела в векторе дел
param[out] результат удаления
*/
bool CaseList::DeleteCase(size_t index)
{
	if (index < 0 || index >= this->_caseList.size())
		return false;
	this->_caseList.erase(this->_caseList.begin() + index);
	return true;
}

/*!
\brief метод возвращающий количество дел в списке
*/
size_t CaseList::Size() const
{
	return this->_caseList.size();
}

/*!
\brief метод для сортировки дел по дате
*/
void CaseList::SortCaseListByDate()
{
	/*for (size_t i = 0; i < this->Size() - 1; i++)
	{
		std::unique_ptr<Case> tmp_case;
		size_t index = i;
		for (size_t j = i + 1; j < this->Size(); j++)
		{
			if (_caseList.at(i)->GetDate() > _caseList.at(j)->GetDate())
			{
				tmp_case.reset();
				tmp_case = std::make_unique<Case>(_caseList.at(j)->GetTitle(), _caseList.at(j)->GetDate(), _caseList.at(j)->GetIsDoneMark());
				index = j;
			}
		}
		if (index != i)
		{
			_caseList.at(index).reset();
			_caseList.at(index) = std::make_unique<Case>(*(_caseList.at(i).release()));
			_caseList.at(i).reset();
			_caseList.at(i) = std::make_unique<Case>(*(tmp_case.release()));
		}
	}*/

	std::sort(_caseList.begin(), _caseList.end(), [](const std::unique_ptr<Case>& lhs, const std::unique_ptr<Case>& rhs)
		{
			return lhs.get()->GetDate() < rhs.get()->GetDate();
		});

}

/*!
\brief метод возвращает количество пробелов после названия дела(задачи) до начала даты для выравнивания по ширине.
Количество пробелов получается путём вычитания длины самого длинного названия дела и дела, которое выводится на печать.
\param[in] index индекс дела(задачи) в векторе задач _caseList
\param[out] size_t количество пробелов после выведенного на экран названия дела.
*/
size_t CaseList::GetNumberOfSpaces(size_t index)
{
	size_t maxLength = this->MaxLength();
	return maxLength - this->_caseList.at(index)->GetTitle().size();
}

/*!
\brief метод вызывает метод PrintCase(this->GetNumberOfSpaces(i)) для каждого дела
*/
void CaseList::PrintCaseList()
{

	for (size_t i = 0; i < this->Size(); i++)
	{
		_caseList.at(i)->PrintCase(this->GetNumberOfSpaces(i));
		std::cout << std::endl;
	}
}

/*!
\brief метод для изменения названия дела.
Старое дело по полученному индексу удаляется, а новое вставляется на его место
\param[in] title новое название дела
\param[in] index индекс дела(задачи) в векторе задач _caseList
*/
void CaseList::ChangeTitle(const std::string& title, size_t index)
{
	Date date = this->_caseList.at(index)->GetDate();
	bool isDone = this->_caseList.at(index)->GetIsDoneMark();
	this->DeleteCase(index);
	this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, isDone));
}

/*!
\brief метод для изменения даты дела.
Старое дело по полученному индексу удаляется, а новое вставляется на его место
\param[in] date новая дата дела
\param[in] index индекс дела(задачи) в векторе задач _caseList
*/
void CaseList::ChangeDate(const std::string& date, size_t index)
{
	std::string title = _caseList.at(index)->GetTitle();
	Date newDate(date);
	bool isDone = _caseList.at(index)->GetIsDoneMark();
	this->DeleteCase(index);
	this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, isDone));
}

/*!
\brief метод для отметки о выполнении.
Если отметка "выполнено" уже стоит, то ничего не меняется. Если же стоит отметка "не выполнено", 
то ставится отметка "выполнено".
Старое дело по полученному индексу удаляется, а новое вставляется на его место.
\param[in] index индекс дела(задачи) в векторе задач _caseList
*/
void CaseList::MarkIsDone(size_t index)
{
	if (_caseList.at(index)->GetIsDoneMark() == true)
		return;
	else
	{
		std::string title = _caseList.at(index)->GetTitle();
		Date date = this->_caseList.at(index)->GetDate();
		this->DeleteCase(index);
		this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, true));
	}
}

/*!
\brief метод для отметки о не выполнении.
Если отметка "не выполнено" уже стоит, то ничего не меняется. Если же стоит отметка "выполнено",
то ставится отметка "не выполнено".
Старое дело по полученному индексу удаляется, а новое вставляется на его место.
\param[in] index индекс дела(задачи) в векторе задач _caseList
*/
void CaseList::MarkIsNotDone(size_t index)
{
	if (_caseList.at(index)->GetIsDoneMark() == false)
		return;
	else
	{
		std::string title = _caseList.at(index)->GetTitle();
		Date date = this->_caseList.at(index)->GetDate();
		this->DeleteCase(index);
		this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, false));
	}
}

/*!
\breif метод возвращает указатель на объект класса Case, который находится по переданному индексу в векторе _caseList
param[in] index индекс дела в векторе _caseList
param[out] Case* указатель на объект класса Case
*/
Case* CaseList::GetCase(size_t index) const
{
	return _caseList.at(index).get();
}

/*!
\brief метод для очистки всего списка дел
*/
void CaseList::Clear()
{
	_caseList.clear();
}

