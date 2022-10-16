#pragma once
#include <vector>
#include "InputDataStream.h"

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t> & input);

	bool IsEOF() const override;

	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t>& m_input;
};
