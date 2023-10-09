#pragma once
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

class WindStats
{
public:
	void Update(double degree, double speed)
	{
		m_sinSum += speed * sin(degree * (M_PI / 180));
		m_cosSum += speed * cos(degree * (M_PI / 180));
		m_measurementsCount++;
	}

	std::tuple<double, double> Average() const
	{
		const double sinSum = m_sinSum / m_measurementsCount;
		const double cosSum = m_cosSum / m_measurementsCount;

		return
		{
			sqrt(cosSum * cosSum + sinSum * sinSum),
			std::fmod((atan2(sinSum, cosSum) * 180 / M_PI) + 360, 360)
		};

	}
private:
	double m_sinSum = 0;
	double m_cosSum = 0;
	size_t m_measurementsCount = 0;
};
