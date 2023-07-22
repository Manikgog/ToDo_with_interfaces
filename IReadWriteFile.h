#ifndef _IREADWRITEFILE_H_
#define _IREADWRITEFILE_H_

#include <vector>
#include <memory>
#include <fstream>
#include "Case.h"


class IReadWriteBinaryFile
{

public:
	IReadWriteBinaryFile() = default;
	~IReadWriteBinaryFile() {}
	virtual std::vector<std::unique_ptr<Case>> ReadBinaryFile() = 0;
	virtual bool WriteBinaryFile(std::vector<std::unique_ptr<Case>>& list) = 0;

};





#endif // !_IREADWRITEFILE_H_

