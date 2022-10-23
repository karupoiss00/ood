#pragma once
#include <sstream>
#include <string>
#include "ICanvas.h"

class SVGCanvas : public ICanvas
{
public:
	explicit SVGCanvas() = delete;
	SVGCanvas(std::string const& fileName);

	void SetColor(Color color) override;
	void DrawLine(Vec2 from, Vec2 to) override;
	void DrawEllipse(Vec2 topLeft, unsigned width, unsigned height) override;

	void Save();
private:
	Color m_currentColor;
	std::stringstream m_outputSvg;
	std::string m_outputFileName;
};