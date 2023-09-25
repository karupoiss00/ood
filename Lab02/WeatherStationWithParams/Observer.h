#pragma once

#include <set>
#include <functional>
#include <map>
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
	virtual void NotifyObservers() = 0;
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
		m_observers.insert(std::make_pair(subscribeParameter, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		std::set<Parameter> changedParams = GetParametersData();

		auto observers = m_observers;
		for (auto it = observers.rbegin(); it != observers.rend(); ++it)
		{
			if (changedParams.contains(it->first))
			{
				it->second->Update(data, it->first);
			}
		}
	}

	void RemoveObserver(Observer& observer) override
	{
		auto i = std::find_if(m_observers.begin(), m_observers.end(), [&](auto& it) {
			return it.second == &observer;
			});
		if (i != m_observers.end())
		{
			m_observers.erase(i->first);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;
	virtual std::set<Parameter> GetParametersData() const = 0;

private:
	std::multimap<Parameter, Observer*> m_observers;
};