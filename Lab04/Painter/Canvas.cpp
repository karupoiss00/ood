#include "SVGCanvas.h"

using namespace std;

SVGCanvas::SVGCanvas(std::string const& fileName)
	: m_currentColor(Color::BLACK)
{

}

/*
SVGCanvas(std::string const& fileName);

	void SetColor(Color color) override;
	void DrawLine(Vec2 from, Vec2 to) override;
	void DrawEllipse(Vec2 topLeft, unsigned width, unsigned height) override;

	void Save();
*/