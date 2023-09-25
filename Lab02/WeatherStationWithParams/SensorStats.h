#pragma once
#include <iostream>
#include <climits>

class SensorStats
{
public:
	void Update(double newValue)
	{
		if (m_minValue > newValue)
		{
			m_minValue = newValue;
		}
		if (m_maxValue < newValue)
		{
			m_maxValue = newValue;
		}
		m_accumulatedValues += newValue;
		++m_countAccumulates;
	}

	double Min() const
	{
		return m_minValue;
	}

	double Max() const
	{
		return m_maxValue;
	}

	double Average() const
	{
		return m_accumulatedValues / m_countAccumulates;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accumulatedValues = 0;
	unsigned m_countAccumulates = 0;
}; 
