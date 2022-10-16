#include "CompressOutputData.h"

using namespace std;

CCompressOutputData::CCompressOutputData(IOutputDataStreamPtr&& stream)
	: COutputDataStreamDecorator(move(stream)),
	m_lastCompressedValue(0), m_lastCompressedCount(0)
{
}

CCompressOutputData::~CCompressOutputData()
{
	try
	{
		Flush();
	}
	catch (...)
	{

	}
}

void CCompressOutputData::WriteByte(uint8_t data)
{
	WriteCompressBlock(&data, 1);
}

void CCompressOutputData::WriteBlock(const void* srcData, streamsize size)
{
	WriteCompressBlock(static_cast<const uint8_t*>(srcData), size);
}

void CCompressOutputData::WriteCompressBlock(const uint8_t* srcData, streamsize size)
{
	streamsize pos = 0;

	while (pos < size)
	{
		if (m_lastCompressedCount && m_lastCompressedValue != srcData[pos])
		{
			Flush();
		}

		m_lastCompressedValue = srcData[pos];
		++m_lastCompressedCount;

		if (m_lastCompressedCount == 255)
		{
			Flush();
		}

		++pos;
	}
}

void CCompressOutputData::Flush()
{
	if (m_lastCompressedCount)
	{
		COutputDataStreamDecorator::WriteByte(m_lastCompressedValue);
		COutputDataStreamDecorator::WriteByte(m_lastCompressedCount);

		m_lastCompressedCount = 0;
	}
}