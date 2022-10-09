#include <string>
#include <catch2/catch.hpp>
#include "../WeatherStation/Observer.h"

using namespace std;

// узнать, что происходит с итератором в коллекции

class ObserverSelfkiller : public IObserver<string>
{
public:
	ObserverSelfkiller(IObservable<string>& observable)
		: m_observable(&observable)
	{
		
	}

	void Update(const string& data) override
	{
		REQUIRE(m_observable);
		REQUIRE(data == "delta");

		m_observable->RemoveObserver(*this);
		REQUIRE(m_observable->IsObserverRegistered(*this));
	}
private:
	IObservable<string>* m_observable;
};

class CleverObservable : public CObservable<string>
{
public:
	void DataChanged()
	{
		NotifyObservers();
	}

protected:
	string GetChangedData() const override
	{
		return "delta";
	}
};

TEST_CASE("removing observer in notifying time")
{
	CleverObservable observable;
	ObserverSelfkiller observer(observable);

	observable.RegisterObserver(observer);
	observable.DataChanged();

	REQUIRE(!observable.IsObserverRegistered(observer));
}