#pragma once

#include <set>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
	virtual bool IsObserverRegistered(IObserver<T>& observer) const = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType & observer) override
	{
		m_observers.insert(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		m_isNotifying = true;

		for (auto& observer : m_observers)
		{
			observer->Update(data);
		}

		m_isNotifying = false;

		if (!m_observersToRemove.empty())
		{
			ClearObserversToRemove();
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		if (!m_isNotifying)
		{
			m_observers.erase(&observer);
		}
		else
		{
			m_observersToRemove.insert(&observer);
		}
	}

	bool IsObserverRegistered(ObserverType& observer) const
	{
		return m_observers.find(&observer) != m_observers.cend();
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	void ClearObserversToRemove()
	{
		for (auto& observer : m_observersToRemove)
		{
			m_observers.erase(observer);
		}

		m_observersToRemove.clear();
	}

	std::set<ObserverType *> m_observers;
	std::set<ObserverType *> m_observersToRemove;

	bool m_isNotifying;
};
