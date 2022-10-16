#include "CryptOutputData.h"

using namespace std;

CCryptOutputData::CCryptOutputData(IOutputDataStreamPtr&& stream, int32_t key, bool encrypt)
	: COutputDataStreamDecorator(move(stream)), m_cryptographer(CCryptographer(key)), m_encrypt(encrypt)
{
}

void CCryptOutputData::WriteByte(uint8_t data)
{
	COutputDataStreamDecorator::WriteByte(m_cryptographer.Encrypt(data));
}

void CCryptOutputData::WriteBlock(const void* srcData, streamsize size)
{
	unsigned pos = 0;
	vector<uint8_t> cryptData(static_cast<unsigned>(size));
	const uint8_t* data = static_cast<const uint8_t*>(srcData);

	while (pos < size)
	{
		cryptData[pos] = m_cryptographer.Encrypt(data[pos]);
		++pos;
	}

	COutputDataStreamDecorator::WriteBlock(&cryptData[0], size);
}