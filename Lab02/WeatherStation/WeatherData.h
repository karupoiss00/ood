#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;

	std::string senderId;
};

class CWeatherData : public CObservable<SWeatherInfo>
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
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windDirection, double windSpeed)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windDirection = std::fmod(windDirection, 360);
		m_windSpeed = windSpeed;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData() const override
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
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
	double m_windDirection = 0.0;
	double m_windSpeed = 0.0;

	std::string m_id;
};
