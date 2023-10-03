#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include "../WeatherStation/WeatherData.h"
#include "../WeatherStation/WeatherDataPro.h"
#include "../WeatherStation/Display.h"

using namespace std;

class CDisplayWithLastNotifierId : public CDisplay
{
public:
	CDisplayWithLastNotifierId(const CWeatherData& weatherDataIn, const CWeatherDataPro& weatherDataOut)
		: CDisplay(weatherDataIn, weatherDataOut)
	{}
	string lastNotifierId;
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		lastNotifierId = data.senderId;
	}
};

TEST_CASE("check that different observables notifying observer")
{
	CWeatherData in("in");
	CWeatherDataPro out("out");

	CDisplayWithLastNotifierId display(in, out);
	in.RegisterObserver(display);
	out.RegisterObserver(display);

	in.SetMeasurements(3, 0.7, 760);

	REQUIRE(display.lastNotifierId == "in");

	out.SetMeasurements(4, 0.8, 761, 240, 20);

	REQUIRE(display.lastNotifierId == "out");
}