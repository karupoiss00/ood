#pragma once
#include <vector>
#include "OutputDataStream.h"

class CMemoryOutputStream : public IOutputDataStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t> & output);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::vector<uint8_t>& m_output;
};