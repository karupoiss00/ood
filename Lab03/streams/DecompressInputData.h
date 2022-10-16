#pragma once
#include "InputStreamDecorator.h"

class CDecompressInputData : public CInputDataStreamDecorator
{
public:
	CDecompressInputData(IInputDataStreamPtr&& stream);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	void ReadCompressedBlock();

	uint8_t m_lastCompressedValue;
	uint8_t m_lastCompressedCount;
};