#pragma once
#include <fstream>
#include "OutputDataStream.h"

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(std::string const& filename);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_file;
};