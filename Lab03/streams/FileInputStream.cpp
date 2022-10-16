#include "FileInputStream.h"

using namespace std;

CFileInputStream::CFileInputStream(string const& filename)
	: m_file(filename, ios_base::in | ios::binary)
{
	if (!m_file.is_open())
	{
		throw ios_base::failure("Failed to open " + filename);
	}
}

bool CFileInputStream::IsEOF() const
{
	return m_file.eof();
}

uint8_t CFileInputStream::ReadByte()
{
	char buf;
	m_file.read(&buf, 1);

	return static_cast<uint8_t>(buf);
}

streamsize CFileInputStream::ReadBlock(void* dstBuffer, streamsize size)
{
	m_file.read(static_cast<char*>(dstBuffer), size);
	return m_file.gcount();
}