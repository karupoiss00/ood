#pragma once

#include <iostream>
#include <cstdint>
#include <memory>

class IOutputDataStream
{
public:

	// Записывает в поток данных байт. В случае ошибки  
	// выбрасывает исключение std::ios_base::failure 
	virtual void WriteByte(uint8_t data) = 0;

	// Записывает в поток блок данных размером size байт, располагающийся по адресу
	// srcData, в случае ошибки выбрасывает исключение std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() {};
};

using IOutputDataStreamPtr = std::unique_ptr<IOutputDataStream>;