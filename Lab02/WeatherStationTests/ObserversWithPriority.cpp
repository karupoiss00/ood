#include <iostream>
#include <string>
#include <catch2/catch.hpp>
#include "../WeatherStation/Observer.h"

using namespace std;

class Observable : public CObservable<string>
{
public:
	void DataChanged()
	{
		NotifyObservers();
	}

	void AddToCallTrace(string value)
	{
		m_observersCallTrace += value;
	}

	string ObserverCallTrace()
	{
		return m_observersCallTrace;
	}
protected:
	string GetChangedData() const override
	{
		return "delta";
	}
private:
	string m_observersCallTrace;
};

class Observer : public IObserver<string>
{
public:
	using Priority = CObservable<string>::Priority;

	Observer(Observable& observable, Priority priority)
		: m_observable(&observable), m_priority(priority)
	{

	}

	void Update(const string& data) override
	{
		m_observable->AddToCallTrace(to_string(m_priority));
	}

	Priority GetPriority()
	{
		return m_priority;
	}
private:
	Observable* m_observable;
	Priority m_priority;
};

TEST_CASE("check priority sequence of notifying")
{
	Observable observable;
	vector<Observer> observers = { Observer(observable, 1), Observer(observable, 2), Observer(observable, 3), };

	for (auto& observer : observers)
	{
		observable.RegisterObserver(observer, observer.GetPriority());
	}

	observable.DataChanged();

	REQUIRE(observable.ObserverCallTrace() == "321");
}

TEST_CASE("check priority sequence of notifying: all have equal priority")
{
	Observable observable;
	vector<Observer> observers = { Observer(observable, 1), Observer(observable, 1), Observer(observable, 1), };

	for (auto& observer : observers)
	{
		observable.RegisterObserver(observer, observer.GetPriority());
	}

	observable.DataChanged();

	REQUIRE(observable.ObserverCallTrace() == "111");
}