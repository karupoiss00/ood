#include "CryptInputData.h"

using namespace std;

CDecryptInputData::CDecryptInputData(IInputDataStreamPtr&& stream, int32_t key, bool encrypt)
	: CInputDataStreamDecorator(move(stream)), m_cryptographer(CCryptographer(key)), m_encrypt(encrypt)
{
}

bool CDecryptInputData::IsEOF() const
{
	return CInputDataStreamDecorator::IsEOF();
}

uint8_t CDecryptInputData::ReadByte()
{
	return Crypt(CInputDataStreamDecorator::ReadByte());
}

streamsize CDecryptInputData::ReadBlock(void* dstBuffer, streamsize size)
{
	auto gcount = CInputDataStreamDecorator::ReadBlock(dstBuffer, size);
	uint8_t* data = static_cast<uint8_t*>(dstBuffer);

	for (streamsize i = 0; i < gcount; ++i)
	{
		data[i] = Crypt(data[i]);
	}

	return gcount;
}

uint8_t CDecryptInputData::Crypt(uint8_t data)
{
	return m_encrypt ? m_cryptographer.Encrypt(data) : m_cryptographer.Decrypt(data);
}