#pragma once
#include "IShapes.h"

class IShapeGroup : public IShape, public IShapes
{
public:
	virtual ~IShapeGroup() = default;
};