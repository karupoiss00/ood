#pragma once
#include "Beverages.h"

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 30;
	}
};

// Цейлонский
class CCeylonTea : public CTea
{
public:
	CCeylonTea()
		:CTea("Ceylon tea")
	{}

	double GetCost() const override
	{
		return 40;
	}
};

// Шу-пуэр
class CShuPuErh : public CTea
{
public:
	CShuPuErh()
		:CTea("Shu pu-erh tea")
	{}

	double GetCost() const override
	{
		return 100;
	}
};

// Шен-пуэр
class CShenPuErh : public CTea
{
public:
	CShenPuErh()
		:CTea("Shen pu-erh tea")
	{}

	double GetCost() const override
	{
		return 130;
	}
};

// oolong te guan yin
class COolongTeGuanYin : public CTea
{
public:
	COolongTeGuanYin()
		:CTea("Oolong te guan yin tea")
	{}

	double GetCost() const override
	{
		return 80;
	}
};