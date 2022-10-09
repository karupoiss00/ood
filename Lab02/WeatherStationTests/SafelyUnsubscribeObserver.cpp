#include <string>
#include <catch2/catch.hpp>
#include "../WeatherStation/Observer.h"

using namespace std;

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

class ObserverObservableOwner: public IObserver<string>
{
public:
	ObserverObservableOwner(IObservable<string>& observable)
		: m_observable(&observable)
	{

	}
protected:
	IObservable<string>* m_observable;
};


class ObserverSelfkiller : public ObserverObservableOwner
{
public:
	ObserverSelfkiller(IObservable<string>& observable)
		: ObserverObservableOwner(observable)
	{

	}
	void Update(const string& data) override
	{
		REQUIRE(m_observable);
		REQUIRE(data == "delta");

		m_observable->RemoveObserver(*this);
		REQUIRE(m_observable->IsObserverRegistered(*this));
	}
};


class ObserverSelfResubscriber : public ObserverObservableOwner
{
public:
	ObserverSelfResubscriber(IObservable<string>& observable)
		: ObserverObservableOwner(observable)
	{

	}
	void Update(const string& data) override
	{
		REQUIRE(m_observable);
		REQUIRE(data == "delta");

		m_observable->RemoveObserver(*this);
		REQUIRE(m_observable->IsObserverRegistered(*this));
		m_observable->RegisterObserver(*this, 1);
		REQUIRE(m_observable->IsObserverRegistered(*this));
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


TEST_CASE("removing and subscribing in notifying time")
{
	CleverObservable observable;
	ObserverSelfResubscriber observer(observable);

	observable.RegisterObserver(observer);
	observable.DataChanged();

	REQUIRE(observable.IsObserverRegistered(observer));
}