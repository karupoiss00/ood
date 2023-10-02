#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherData in("in");
	CWeatherData out("out");

	CDisplay display;
	in.RegisterObserver(display, WeatherParameter::TEMPERATURE);
	in.RegisterObserver(display, WeatherParameter::PRESSURE);
	out.RegisterObserver(display, WeatherParameter::HUMIDITY);

	CStatsDisplay statsDisplay;
	in.RegisterObserver(statsDisplay, WeatherParameter::PRESSURE);
	out.RegisterObserver(statsDisplay, WeatherParameter::WIND);

	in.SetMeasurements(3, 0.7, 765, 0, 0);
	out.SetMeasurements(4, 0.8, 761, 0, 10);
	out.SetMeasurements(1, 0.7, 763, 270, 10);
	return 0;
}