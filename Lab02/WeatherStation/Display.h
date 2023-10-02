#pragma once
#include <iostream>
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo>
{
public: 
	CDisplay(const CWeatherData& weatherDataIn, const CWeatherDataPro& weatherDataOut)
		: m_weatherDataIn(weatherDataIn), m_weatherDataOut(weatherDataOut)
	{}
private:
	/* 
		����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		if (&observable == &m_weatherDataOut)
		{
			std::cout << "Sensor ID: " << data.senderId << std::endl;
			std::cout << "Current Temp " << data.temperature << std::endl;
			std::cout << "Current Humidity " << data.humidity << std::endl;
			std::cout << "Current Pressure " << data.pressure << std::endl;
			std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
			std::cout << "Current Wind Direction " << data.windDirection << std::endl;
			std::cout << "----------------" << std::endl;
		}
		
		if (&observable == &m_weatherDataIn)
		{
			std::cout << "Sensor ID: " << data.senderId << std::endl;
			std::cout << "Current Temp " << data.temperature << std::endl;
			std::cout << "Current Humidity " << data.humidity << std::endl;
			std::cout << "Current Pressure " << data.pressure << std::endl;
			std::cout << "----------------" << std::endl;
		}
	}

	CWeatherData const& m_weatherDataIn;
	CWeatherDataPro const& m_weatherDataOut;
};