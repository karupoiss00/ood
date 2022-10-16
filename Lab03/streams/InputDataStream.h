#pragma once

#include <iostream>
#include <cstdint>

class IInputDataStream
{
public:
	// ���������� ������� ���������� ����� ������ ������.
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual bool IsEOF() const = 0;

	// ��������� ���� �� ������. ����������� ����������
	// std::ios_base::failure � ������ ������
	virtual uint8_t ReadByte() = 0;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer. ���������� ���������� ������� ����������� ����. 
	// ����������� ���������� � ������ ������
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

	virtual ~IInputDataStream() {};
};

using IInputDataStreamPtr = std::unique_ptr<IInputDataStream>;