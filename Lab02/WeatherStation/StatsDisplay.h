#pragma once
#include <iostream>
#include <climits>
#include "WeatherData.h"
#include "SensorStats.h"

struct SensorKit
{
	SensorStats m_temperatureStats;
	SensorStats m_pressureStats;
	SensorStats m_humidityStats;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	using SensorKits = std::map<std::string, std::shared_ptr<SensorKit>>;
	/*
		Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Sensor ID: " << data.senderId << std::endl;

		if (m_sensors.find(data.senderId) == m_sensors.cend())
		{
			CreateSensorKit(data.senderId);
		}

		std::shared_ptr<SensorKit> sensorKit = m_sensors[data.senderId];

		UpdateSensor(sensorKit, data);
		ShowSensorKitStats(sensorKit);
	}

	void ShowSensorStatistic(std::string sensorName, SensorStats stats)
	{
		std::cout << "Max " << sensorName << " " << stats.Max() << std::endl;
		std::cout << "Min " << sensorName << " " << stats.Min() << std::endl;
		std::cout << "Average " << sensorName << " " << stats.Average() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void ShowSensorKitStats(std::shared_ptr<SensorKit>& sensorKit)
	{
		ShowSensorStatistic("temp", sensorKit->m_temperatureStats);
		ShowSensorStatistic("pressure", sensorKit->m_pressureStats);
		ShowSensorStatistic("temp", sensorKit->m_humidityStats);
	}

	void UpdateSensor(std::shared_ptr<SensorKit>& sensorKit, SWeatherInfo const& data)
	{
		sensorKit->m_temperatureStats.Update(data.temperature);
		sensorKit->m_humidityStats.Update(data.humidity);
		sensorKit->m_pressureStats.Update(data.pressure);
	}

	void CStatsDisplay::CreateSensorKit(std::string id)
	{
		m_sensors.emplace(make_pair(id, std::make_shared<SensorKit>()));
	}

	SensorKits m_sensors;
};
