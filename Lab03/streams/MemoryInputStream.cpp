#include "MemoryInputStream.h"

using namespace std;

CMemoryInputStream::CMemoryInputStream(std::vector<uint8_t> & input)
	: m_input(input)
{

}

bool CMemoryInputStream::IsEOF() const
{
	return m_input.empty();
}

uint8_t CMemoryInputStream::ReadByte()
{
	uint8_t readByte = *m_input.begin();
	m_input.erase(m_input.begin());

	return readByte;
}

streamsize CMemoryInputStream::ReadBlock(void* dstBuffer, streamsize size)
{
	unsigned realReadBytes = 0;
	uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
	for (unsigned i = 0; i < size; i++)
	{
		if (IsEOF())
		{
			break;
		}
		if (buffer == nullptr)
		{
			throw std::invalid_argument("destination buffer null pointer exeption");
		}

		buffer[i] = ReadByte();
		realReadBytes++;
	}
	return realReadBytes;
}