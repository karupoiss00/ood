#pragma once
#include <QWidget>
#include "IDrawingStrategyFactory.h"
#include "PenStrategy.h"
#include "Image.h"

class DrawingStrategyFactory : public IDrawingStrategyFactory
{
public:
	DrawingStrategyFactory()
		: m_penStrategy(nullptr)
	{
	}

	DrawingStrategyFactory(std::shared_ptr<Image> image, QWidget* view)
		: m_penStrategy(std::make_shared<PenStrategy>(image, view))
	{

	}

	std::shared_ptr<IDrawingStrategy> GetStrategy(std::string type) override
	{
		return m_penStrategy;
	}

private:
	std::shared_ptr<PenStrategy> m_penStrategy;
};