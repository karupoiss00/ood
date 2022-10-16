#include "FileOutputStream.h"

using namespace std;

CFileOutputStream::CFileOutputStream(const string& filename)
	: m_file(filename, ios_base::out | ios::binary)
{
	if (!m_file.is_open())
	{
		throw ios_base::failure("Failed to open " + filename);
	}
}

void CFileOutputStream::WriteByte(uint8_t data)
{
	m_file << data;
}

void CFileOutputStream::WriteBlock(const void* srcData, streamsize size)
{
	m_file.write(static_cast<const char*>(srcData), size);
}