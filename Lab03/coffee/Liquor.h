#pragma once
#include "Condiment.h"

// Тип ликёра
enum class LiquorType
{
	Chocolate,	// Шоколадный
	Nut,		// Кленовый
};

// Добавка "Ликёр"
class CLiquor : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr&& beverage, LiquorType LiquorType)
		: CCondimentDecorator(move(beverage))
		, m_liquorType(LiquorType)
	{}
protected:
	double GetCondimentCost() const override
	{
		return 50;
	}
	std::string GetCondimentDescription() const override
	{
		return std::string(m_liquorType == LiquorType::Chocolate ? "Chocolate" : "Nut")
			+ " liquor";
	}
private:
	LiquorType m_liquorType;
};