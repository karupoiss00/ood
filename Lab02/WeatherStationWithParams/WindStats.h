#pragma once
#include <iostream>
#include <climits>

class WindDirectionStats
{
public:
	void Update(double newValue)
	{
		m_accumulatedValues += newValue;
		++m_countAccumulates;
	}

	double Average() const
	{
		return std::fmod(m_accumulatedValues / m_countAccumulates, 360);
	}

private:
	double m_accumulatedValues = 0;
	unsigned m_countAccumulates = 0;
};
