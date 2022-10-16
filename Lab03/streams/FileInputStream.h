#pragma once
#include <fstream>
#include "InputDataStream.h"

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(std::string const& filename);

	bool IsEOF() const override;

	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_file;
};
