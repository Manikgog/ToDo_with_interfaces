#ifndef _REDWRITEFILE_H_
#define _REDWRITEFILE_H_

#include <fstream>
#include "IReadWriteFile.h"


class ReadWriteBinaryFile : public  IReadWriteBinaryFile
{
public:
	ReadWriteBinaryFile() = default;
	ReadWriteBinaryFile(std::string filename) : _filename(filename) {}

	~ReadWriteBinaryFile()
	{}

	std::vector<std::unique_ptr<Case>> ReadBinaryFile() override;

	bool WriteBinaryFile(std::vector<std::unique_ptr<Case>>& list) override;
	
private:
	std::string _filename;
	static const size_t _sizeTitle = 56;
};



#endif