#pragma once

#include <set>
#include <functional>
#include <map>
#include <ranges>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T, typename Parameter>
class IObserver
{
public:
	virtual void Update(T const& data, Parameter changedParam) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, typename Parameter>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, Parameter>& observer, Parameter paramToObserve) = 0;
	virtual void NotifyObservers(Parameter changedParam) = 0;
	virtual void RemoveObserver(IObserver<T, Parameter>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T, class Parameter>
class CObservable : public IObservable<T, Parameter>
{
public:
	using Observer = IObserver<T, Parameter>;

	void RegisterObserver(Observer& observer, Parameter subscribeParameter) override
	{
		RemoveObserver(observer);
		m_observers.emplace(&observer, subscribeParameter);
	}

	void NotifyObservers(Parameter changedParam) override
	{
		T data = GetChangedData();

		for (auto [observer, param] : m_observers)
		{
			if (param == changedParam)
			{
				observer->Update(data, changedParam);
			}
		}
	}

	void RemoveObserver(Observer& observer) override
	{
		m_observers.erase(&observer);
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	// вернуть приоритеты, сделать быстро
	std::multimap<Observer*, Parameter> m_observers;
};