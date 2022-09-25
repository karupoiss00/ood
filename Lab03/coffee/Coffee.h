#pragma once
#include "Beverages.h"

// ����
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// ���������
class CCappuccino : public CCoffee
{
public:
	CCappuccino()
		:CCoffee("Cappuccino")
	{}

	double GetCost() const override
	{
		return 80;
	}
};

// ������� ���������
class CDoubleCappuccino : public CCoffee
{
public:
	CDoubleCappuccino()
		:CCoffee("Double cappuccino")
	{}

	double GetCost() const override
	{
		return 120;
	}
};


// �����
class CLatte : public CCoffee
{
public:
	CLatte()
		:CCoffee("Latte")
	{}

	double GetCost() const override
	{
		return 90;
	}
};

// ������� �����
class CDoubleLatte : public CCoffee
{
public:
	CDoubleLatte()
		:CCoffee("Double latte")
	{}

	double GetCost() const override
	{
		return 130;
	}
};