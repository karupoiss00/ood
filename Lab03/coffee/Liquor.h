#pragma once
#include "Condiment.h"

// ��� �����
enum class LiquorType
{
	Chocolate,	// ����������
	Nut,		// ��������
};

// ������� "����"
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