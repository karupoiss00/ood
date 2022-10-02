#pragma once
#include "Condiment.h"

class CChocolateBars : public CCondimentDecorator
{
public:
	CChocolateBars(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CCondimentDecorator(move(beverage)), m_quantity(quantity)
	{
		if (m_quantity > 5)
		{
			cout << "unsupported count of chocolate bars (" << quantity << ")" << endl;
			m_quantity = 5;
		}
	}
protected:
	double GetCondimentCost()const override
	{
		return 10.0 * m_quantity;
	}
	std::string GetCondimentDescription()const override
	{
		return "Chocolate bar x " + std::to_string(m_quantity);
	}
private:
	unsigned m_quantity;
};
