#pragma once
#include <iostream>
#include <climits>
#include "WeatherData.h"
#include "SensorStats.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStats.Update(data.temperature);
		m_pressureStats.Update(data.pressure);
		m_humidityStats.Update(data.humidity);

		ShowSensorStatistic("Temp", m_temperatureStats);
		ShowSensorStatistic("Pressure", m_pressureStats);
		ShowSensorStatistic("Humidity", m_humidityStats);
	}

	void ShowSensorStatistic(std::string sensorName, SensorStats stats)
	{
		std::cout << "Max " << sensorName << " " << stats.Max() << std::endl;
		std::cout << "Min " << sensorName << " " << stats.Min() << std::endl;
		std::cout << "Average " << sensorName << " " << stats.Average() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	SensorStats m_temperatureStats;
	SensorStats m_pressureStats;
	SensorStats m_humidityStats;
};
