#pragma once
#include "OutputStreamDecorator.h"
#include "Crypter.h"

class CCryptOutputData : public COutputDataStreamDecorator
{
public:
	CCryptOutputData(IOutputDataStreamPtr&& stream, int32_t key, bool encrypt = true);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	CCryptographer m_cryptographer;
	bool m_encrypt;
};