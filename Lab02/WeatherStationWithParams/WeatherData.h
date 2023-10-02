#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include "SWeatherInfo.h"

class CWeatherData : public CObservable<SWeatherInfo, WeatherParameter>
{
public:
	CWeatherData(std::string id)
		: m_id(id)
	{

	}

	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}
	// Скорость ветра (в м/с)
	double GetWindSpeed() const
	{
		return m_windSpeed;
	}
	// Направление ветра (в градусах)
	double GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		for (auto param : m_changedParams)
		{
			NotifyObservers(param);
		}
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windDirection, double windSpeed)
	{
		UpdateChangedData(temp, humidity, pressure, windDirection, windSpeed);

		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windDirection = std::fmod(windDirection, 360);
		m_windSpeed = windSpeed;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData() const
	{
		SWeatherInfo info;

		info.senderId = m_id;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windDirection = GetWindDirection();
		info.windSpeed = GetWindSpeed();

		return info;
	}

private:
	void UpdateChangedData(double temp, double humidity, double pressure, double windDirection, double windSpeed)
	{
		m_changedParams.clear();

		if (temp != m_temperature)
		{
			m_changedParams.emplace(WeatherParameter::TEMPERATURE);
		}
		if (humidity != m_humidity)
		{
			m_changedParams.emplace(WeatherParameter::HUMIDITY);
		}
		if (pressure != m_pressure)
		{
			m_changedParams.emplace(WeatherParameter::PRESSURE);
		}
		if (windSpeed != m_windSpeed || windDirection != m_windDirection)
		{
			m_changedParams.emplace(WeatherParameter::WIND);
		}
	}

	std::set<WeatherParameter> m_changedParams;

	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windDirection = 0.0;
	double m_windSpeed = 0.0;

	std::string m_id;
};
