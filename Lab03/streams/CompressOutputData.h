#pragma once
#include "OutputStreamDecorator.h"

class CCompressOutputData : public COutputDataStreamDecorator
{
public:
	CCompressOutputData(IOutputDataStreamPtr&& stream);
	~CCompressOutputData();

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;
	void Flush();

protected:
	void WriteCompressBlock(const uint8_t* srcData, std::streamsize size);

private:
	uint8_t m_lastCompressedValue;
	uint8_t m_lastCompressedCount;
};