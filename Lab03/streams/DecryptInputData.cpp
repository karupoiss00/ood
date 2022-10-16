#include "DecryptInputData.h"

using namespace std;

CDecryptInputData::CDecryptInputData(IInputDataStreamPtr&& stream, int32_t key)
	: CInputDataStreamDecorator(move(stream)), m_cryptographer(CCryptographer(key))
{
}

bool CDecryptInputData::IsEOF() const
{
	return CInputDataStreamDecorator::IsEOF();
}

uint8_t CDecryptInputData::ReadByte()
{
	return m_cryptographer.Decrypt(CInputDataStreamDecorator::ReadByte());
}

streamsize CDecryptInputData::ReadBlock(void* dstBuffer, streamsize size)
{
	auto gcount = CInputDataStreamDecorator::ReadBlock(dstBuffer, size);
	uint8_t* data = static_cast<uint8_t*>(dstBuffer);

	for (streamsize i = 0; i < gcount; ++i)
	{
		data[i] = m_cryptographer.Decrypt(data[i]);
	}

	return gcount;
}