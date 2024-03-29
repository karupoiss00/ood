#pragma once

#include <iostream>
#include <cstdint>
#include <memory>

class IOutputDataStream
{
public:

	// ���������� � ����� ������ ����. � ������ ������  
	// ����������� ���������� std::ios_base::failure 
	virtual void WriteByte(uint8_t data) = 0;

	// ���������� � ����� ���� ������ �������� size ����, ��������������� �� ������
	// srcData, � ������ ������ ����������� ���������� std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() {};
};

using IOutputDataStreamPtr = std::unique_ptr<IOutputDataStream>;