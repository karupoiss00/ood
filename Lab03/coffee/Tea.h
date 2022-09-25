#pragma once
#include "Beverages.h"

// ���
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

// ����������
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

// ��-����
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

// ���-����
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