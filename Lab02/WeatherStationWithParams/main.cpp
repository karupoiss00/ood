#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherData in("in");
	CWeatherData out("out");

	CDisplay display;
	in.RegisterObserver(display, WeatherParameter::TEMPERATURE);
	out.RegisterObserver(display, WeatherParameter::HUMIDITY);

	CStatsDisplay statsDisplay;
	in.RegisterObserver(statsDisplay, WeatherParameter::PRESSURE);
	out.RegisterObserver(statsDisplay, WeatherParameter::WIND);

	in.SetMeasurements(3, 0.7, 765, 0, 0);
	out.SetMeasurements(4, 0.8, 761, 180, 10);
	out.SetMeasurements(1, 0.7, 763, 360, 2);
	return 0;
}