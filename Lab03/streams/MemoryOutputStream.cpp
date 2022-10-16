#include "MemoryOutputStream.h"

using namespace std;

CMemoryOutputStream::CMemoryOutputStream(std::vector<uint8_t>& output)
	: m_output(output)
{

}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
	m_output.push_back(data);
}

void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* buffer = static_cast<const uint8_t*>(srcData);
	for (unsigned i = 0; i < size; i++)
	{
		if (srcData == nullptr)
		{
			throw std::invalid_argument("src buffer null pointer exeption");
		}

		m_output.push_back(buffer[i]);
	}
}