#include "DecompressInputData.h"

using namespace std;

CDecompressInputData::CDecompressInputData(IInputDataStreamPtr&& stream)
	: CInputDataStreamDecorator(move(stream)),
	m_lastCompressedValue(0), m_lastCompressedCount(0)
{
}

bool CDecompressInputData::IsEOF() const
{
	return m_lastCompressedCount ? false : CInputDataStreamDecorator::IsEOF();
}

uint8_t CDecompressInputData::ReadByte()
{
	ReadCompressedBlock();
	--m_lastCompressedCount;

	return m_lastCompressedValue;
}

streamsize CDecompressInputData::ReadBlock(void* dstBuffer, streamsize size)
{
	streamsize readCount = 0;
	uint8_t* uncompressData = static_cast<uint8_t*>(dstBuffer);

	try
	{
		ReadCompressedBlock();
	}
	catch (const ios_base::failure&)
	{
		return 0;
	}

	while (m_lastCompressedCount && readCount < size)
	{
		uncompressData[readCount] = m_lastCompressedValue;

		--m_lastCompressedCount;
		++readCount;
	}

	return readCount;
}

void CDecompressInputData::ReadCompressedBlock()
{
	if (!m_lastCompressedCount)
	{
		m_lastCompressedValue = CInputDataStreamDecorator::ReadByte();
		m_lastCompressedCount = CInputDataStreamDecorator::ReadByte();

		if (CInputDataStreamDecorator::IsEOF())
		{
			m_lastCompressedCount = 0;
			throw ios_base::failure("End of file");
		}
	}
}
