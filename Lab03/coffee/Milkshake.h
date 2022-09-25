#pragma once
#include "Beverages.h"

#include <map>
#include <stdexcept>

enum class MilkshakeSize {
	Small,
	Medium,
	Large
};


// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size)
		:CBeverage(CreateDescription("milkshake", size)), m_size(size)
	{}

	double GetCost() const override
	{
		return MILKSHAKE_SIZE_PRICE.find(m_size)->second;
	}
private:
	MilkshakeSize m_size;

	using Cost = double;
	const std::map<MilkshakeSize, Cost> MILKSHAKE_SIZE_PRICE =
	{
		{MilkshakeSize::Small, 50},
		{MilkshakeSize::Medium, 60},
		{MilkshakeSize::Large, 80},
	};

	std::string CreateDescription(std::string name, MilkshakeSize size) const
	{
		std::string result;

		switch (size)
		{
		case MilkshakeSize::Small:
			result = "Small";
			break;
		case MilkshakeSize::Medium:
			result = "Medium";
			break;
		case MilkshakeSize::Large:
			result = "Large";
			break;
		default:
			throw std::domain_error("invalid milkshake size");
		}

		result += " " + name;

		return result;
	}
};
