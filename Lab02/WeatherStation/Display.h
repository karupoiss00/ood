#pragma once
#include <iostream>
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* 
		����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Sensor ID: " << data.senderId << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Humidity " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};