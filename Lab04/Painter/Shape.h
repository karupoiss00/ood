#pragma once
#include <memory>
#include "ICanvas.h"
#include "Color.h"

class CShape
{
public:
	CShape();
	explicit CShape(Color color);

	virtual void Draw(ICanvas&) const = 0;

	void Fill(Color color);
	Color GetColor() const;

	virtual ~CShape();
protected:
	Color m_color;
};

using ShapePointer = std::unique_ptr<CShape>;