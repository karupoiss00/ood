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
		m_speedDirPairs.push_back({ speed, degree });
	}

	std::tuple<double, double> Average() const
	{
		double sinSum = 0;
		double cosSum = 0;

		for (auto const& [speed, direction] : m_speedDirPairs)
		{
			sinSum += speed * sin(direction * (M_PI / 180));
			cosSum += speed * cos(direction * (M_PI / 180));
		}
		sinSum = sinSum / m_speedDirPairs.size();
		cosSum = cosSum / m_speedDirPairs.size();

		return
		{
			sqrt(cosSum * cosSum + sinSum * sinSum),
			std::fmod((atan2(sinSum, cosSum) * 180 / M_PI) + 360, 360)
		};

	}
private:
	std::vector<std::pair<double, double>> m_speedDirPairs;
};
