#pragma once

#include <set>
#include <functional>
#include <map>

template <typename T>
class IObservable;

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
	virtual void Update(T const& data, IObservable<T>& observable) = 0;
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
	virtual void RegisterObserver(IObserver<T> & observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
	virtual bool IsObserverRegistered(IObserver<T>& observer) const = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	using Priority = unsigned;
	using Observer = IObserver<T>;

	void RegisterObserver(Observer& observer, Priority priority = 0) override
	{
		if (m_observersToRemove.find(&observer) != m_observersToRemove.cend())
		{
			m_observersToRemove.erase(&observer);
		}

		if (!m_isNotifying)
		{
			RemoveObserverImpl(&observer);

			m_observers.insert(ObserverInfo(&observer, priority));
			m_observersPriority.insert(std::make_pair(&observer, priority));
		}
		else
		{
			m_observersToRegister.insert(ObserverInfo(&observer, priority));
		}
		
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		m_isNotifying = true;

		for (auto observerInfo : m_observers)
		{
			observerInfo.observer->Update(data, *this);
		}

		m_isNotifying = false;

		if (!m_observersToRemove.empty())
		{
			ClearObserversToRemove();
		}

		if (!m_observersToRegister.empty())
		{
			RegisterDefferedSubscribers();
		}
	}

	void RemoveObserver(Observer& observer) override
	{
		if (!m_isNotifying)
		{
			RemoveObserverImpl(&observer);
		}
		else
		{
			m_observersToRemove.insert(&observer);
		}
	}

	bool IsObserverRegistered(Observer& observer) const
	{
		return m_observersPriority.find(&observer) != m_observersPriority.cend();
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	void RemoveObserverImpl(Observer* observer)
	{
		m_observers.erase(ObserverInfo(observer, m_observersPriority[observer]));
		m_observersPriority.erase(observer);
	}

	void RegisterDefferedSubscribers()
	{
		m_observers.merge(m_observersToRegister);
		m_observersToRegister.clear();
	};

	void ClearObserversToRemove()
	{
		for (auto& observer : m_observersToRemove)
		{
			RemoveObserverImpl(observer);
		}

		m_observersToRemove.clear();
	};

	struct ObserverInfo
	{
		ObserverInfo(Observer* _observer, Priority _priority)
			: observer(_observer), priority(_priority)
		{}

		Observer* observer;
		Priority priority;
	};

	struct ObserverInfoComparator
	{
		bool operator()(ObserverInfo const& lhs, ObserverInfo const& rhs) const
		{
			if (lhs.observer == rhs.observer)
			{
				return false;
			}

			if (lhs.priority != rhs.priority)
			{
				return lhs.priority > rhs.priority;
			}

			return lhs.observer < rhs.observer;
		};
	};

	using Observers = std::set<ObserverInfo, ObserverInfoComparator>;

	Observers m_observers;
	Observers m_observersToRegister;
	std::set<Observer*> m_observersToRemove;
	std::map<Observer*, unsigned> m_observersPriority;

	bool m_isNotifying;
};
