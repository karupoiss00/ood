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
	using ObserverInfo = std::pair<Observer*, Priority>;

	void RegisterObserver(Observer& observer, Priority priority = 0) override
	{
		auto alreadySubscribed = [&observer](const ObserverInfo& p)
		{
			return std::addressof(observer) == std::addressof(*p.first);
		};
		auto it = std::find_if(m_observers.cbegin(), m_observers.cend(), alreadySubscribed);

		if (it == m_observers.cend())
		{
			m_observers.insert(ObserverInfo(&observer, priority));
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		m_isNotifying = true;

		for (auto& observer : m_observers)
		{
			observer.first->Update(data);
		}

		m_isNotifying = false;

		if (!m_observersToRemove.empty())
		{
			ClearObserversToRemove();
		}
	}

	void RemoveObserver(Observer& observer) override
	{
		if (!m_isNotifying)
		{
			RemoveObserverImpl(observer);
		}
		else
		{
			m_observersToRemove.insert(&observer);
		}
	}

	bool IsObserverRegistered(Observer& observer) const
	{
		auto comparator = [&observer](const ObserverInfo& p)
		{
			return p.first == &observer;
		};
		auto it = std::find_if(m_observers.cbegin(), m_observers.cend(), comparator);
		return it != m_observers.cend();
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	void RemoveObserverImpl(Observer& observer)
	{
		auto comparator = [&observer](const ObserverInfo& p)
		{
			return p.first == &observer;
		};
		auto it = std::find_if(m_observers.begin(), m_observers.end(), comparator);
		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}
	}

	void ClearObserversToRemove()
	{
		for (auto& observer : m_observersToRemove)
		{
			RemoveObserverImpl(*observer);
		}

		m_observersToRemove.clear();
	}

	struct PriorityComparator
	{
		bool operator()(const ObserverInfo& lhs, const ObserverInfo& rhs) const
		{
			return lhs.second >= rhs.second;
		}
	};

	std::set<ObserverInfo, PriorityComparator> m_observers;
	std::set<Observer*> m_observersToRemove;

	bool m_isNotifying;
};
