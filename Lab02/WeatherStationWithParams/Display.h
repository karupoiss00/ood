#pragma once
#include <iostream>
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo, WeatherParameter>
{
private:
	/* 
		Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, WeatherParameter changedParam) override
	{
		std::cout << "////////////////" << std::endl;
		std::cout << "Sensor ID: " << data.senderId << std::endl;
		std::cout << "////////////////" << std::endl;

		if (changedParam == WeatherParameter::TEMPERATURE)
		{
			std::cout << "Current Temp " << data.temperature << std::endl;
		}
		else if (changedParam == WeatherParameter::HUMIDITY)
		{
			std::cout << "Current Humidity " << data.humidity << std::endl;
		}
		else if (changedParam == WeatherParameter::PRESSURE)
		{
			std::cout << "Current Pressure " << data.pressure << std::endl;
		}
		else if (changedParam == WeatherParameter::WIND)
		{
			std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
			std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
};