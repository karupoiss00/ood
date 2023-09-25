#pragma once
#include <string>

enum class WeatherParameter
{
	TEMPERATURE,
	HUMIDITY,
	PRESSURE,
	WIND,
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;

	std::string senderId;
};