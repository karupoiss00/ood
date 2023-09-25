#include "WeatherData.h"
#include "WeatherDataPro.h"
#include "Display.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherData in("in");
	CWeatherDataPro out("out");

	CDisplay display;
	in.RegisterObserver(display);
	out.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	in.RegisterObserver(statsDisplay);
	out.RegisterObserver(statsDisplay);

	in.SetMeasurements(3, 0.7, 760);
	out.SetMeasurements(4, 0.8, 761, 180, 10);
	out.SetMeasurements(4, 0.8, 761, 360, 2);
	return 0;
}