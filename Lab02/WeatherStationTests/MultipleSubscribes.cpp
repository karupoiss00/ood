#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include "../WeatherStation/WeatherData.h"
#include "../WeatherStation/Display.h"

using namespace std;

class CDisplayWithLastNotifierId : public CDisplay
{
public:
	string lastNotifierId;
private:
	void Update(SWeatherInfo const& data) override
	{
		lastNotifierId = data.senderId;
	}
};

TEST_CASE("check that different observables notifying observer")
{
	CWeatherData in("in");
	CWeatherData out("out");

	CDisplayWithLastNotifierId display;
	in.RegisterObserver(display);
	out.RegisterObserver(display);

	in.SetMeasurements(3, 0.7, 760, 360, 0);

	REQUIRE(display.lastNotifierId == "in");

	out.SetMeasurements(4, 0.8, 761, 360, 10);

	REQUIRE(display.lastNotifierId == "out");
}