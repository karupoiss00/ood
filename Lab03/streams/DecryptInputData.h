#pragma once
#include "InputStreamDecorator.h"
#include "Crypter.h"

class CDecryptInputData : public CInputDataStreamDecorator
{
public:
	CDecryptInputData(IInputDataStreamPtr&& stream, int32_t key);

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

protected:
	uint8_t Decrypt(uint8_t data);

private:
	CCryptographer m_cryptographer;
};