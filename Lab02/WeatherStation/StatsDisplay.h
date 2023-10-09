#pragma once
#include <iostream>
#include <climits>
#include "WeatherData.h"
#include "SensorStats.h"
#include "WindStats.h"

struct SensorKit
{
	SensorStats m_temperatureStats;
	SensorStats m_pressureStats;
	SensorStats m_humidityStats;
	WindStats m_windStats;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(CWeatherData const& weatherDataIn, CWeatherDataPro const& weatherDataOut)
		: m_weatherDataIn(weatherDataIn), m_weatherDataOut(weatherDataOut)
	{}
private:
	using SensorKits = std::map<IObservable<SWeatherInfo>*, std::shared_ptr<SensorKit>>;
	/*
		Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		std::cout << "////////////////" << std::endl;
		std::cout << "Sensor ID: " << data.senderId << std::endl;
		std::cout << "////////////////" << std::endl;

		if (m_sensors.find(&observable) == m_sensors.cend())
		{
			CreateSensorKit(observable);
		}

		std::shared_ptr<SensorKit> sensorKit = m_sensors[&observable];

		UpdateSensor(sensorKit, data);

		if (&observable == &m_weatherDataIn)
		{
			ShowSensorKitStats(sensorKit, false);
		}

		if (&observable == &m_weatherDataOut)
		{
			ShowSensorKitStats(sensorKit, true);
		}
	}
	// слушать решарпер о варнингах
	void ShowSensorStatistic(std::string sensorName, SensorStats stats)
	{
		std::cout << "Max " << sensorName << " " << stats.Max() << std::endl;
		std::cout << "Min " << sensorName << " " << stats.Min() << std::endl;
		std::cout << "Average " << sensorName << " " << stats.Average() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void ShowWindStatistic(WindStats stats)
	{
		auto [speed, direction] = stats.Average();
		std::cout << "Average wind speed: " << speed << std::endl;
		std::cout << "Average wind direction: " << direction << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void ShowSensorKitStats(std::shared_ptr<SensorKit>& sensorKit, bool showWindStats)
	{
		ShowSensorStatistic("temp", sensorKit->m_temperatureStats);
		ShowSensorStatistic("pressure", sensorKit->m_pressureStats);
		ShowSensorStatistic("humidity", sensorKit->m_humidityStats);

		if (showWindStats)
		{
			ShowWindStatistic(sensorKit->m_windStats);
		}
	}

	void UpdateSensor(std::shared_ptr<SensorKit>& sensorKit, SWeatherInfo const& data)
	{
		sensorKit->m_temperatureStats.Update(data.temperature);
		sensorKit->m_humidityStats.Update(data.humidity);
		sensorKit->m_pressureStats.Update(data.pressure);
		sensorKit->m_windStats.Update(data.windDirection, data.windSpeed);
	}

	void CreateSensorKit(IObservable<SWeatherInfo>& observable)
	{
		m_sensors.emplace(&observable, std::make_shared<SensorKit>());
	}

	IObservable<SWeatherInfo> const& m_weatherDataIn;
	IObservable<SWeatherInfo> const& m_weatherDataOut;

	SensorKits m_sensors;
};
