#include "ReadWriteFile.h"

std::vector<std::unique_ptr<Case>> ReadWriteBinaryFile::ReadBinaryFile() 
{
	std::ifstream fin; //< creating an ifstream object to read data from a file
	std::vector<std::unique_ptr<Case>> listCases;
	fin.open(this->_filename, std::ios_base::in | std::ios_base::binary);
	//< writing cases from a file to the listCases array
	//< запись дел из файла в массив listCases
	if (!fin.is_open()) {
		std::cout << "Ошибка открытия файла.\n";
		return listCases;
	}
	else {
		//std::cout << "Файл открыт.\n";
		struct C4se
		{
			char title[_sizeTitle]{};
			Date date;
			bool isDone;
		};
		C4se c4se;
		while (fin.read((char*)&c4se, sizeof(C4se)))
		{
			listCases.push_back(std::make_unique<Case>(c4se.title, c4se.date, c4se.isDone));
		}
	}

	fin.close();
	return listCases;
}

bool ReadWriteBinaryFile::WriteBinaryFile(std::vector<std::unique_ptr<Case>>& list)
{
	std::ofstream fout;
	fout.open(this->_filename, std::ios_base::out | std::ios_base::binary);

	if (!fout.is_open()) {
		std::cout << "Невозможно открыть файл.\n";
		return false;
	}

	struct C4se
	{
		char title[_sizeTitle]{};
		Date date;
		bool isDone{};
	};

	for (int j = 0; j < list.size(); ++j)
	{
		C4se c4se;
		size_t lengthOfTitleString = list.at(j)->GetTitle().size();
		if (lengthOfTitleString >= _sizeTitle)
			lengthOfTitleString = _sizeTitle - 1;
		for (int i = 0; i < lengthOfTitleString; ++i)
		{
			c4se.title[i] = list.at(j).get()->GetTitle().at(i);
		}
		c4se.date = list.at(j).get()->GetDate();
		c4se.isDone = list.at(j).get()->GetIsDoneMark();
		fout.write((char*)&c4se, sizeof(C4se));
	}

	fout.close();
	return true;
}