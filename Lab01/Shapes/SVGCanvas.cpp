#include <fstream>
#include <iostream>
#include "SVGCanvas.h"

using namespace std;
using namespace sfx;

constexpr int STROKE_WIDTH = 4;

SVGCanvas::SVGCanvas(std::string const& fileName)
	: m_outputFileName(fileName), m_currentColor("#000000")
{
	m_outputSvg = stringstream("");
}

void SVGCanvas::Save()
{
	ofstream outputFile(m_outputFileName);

	if (!outputFile.good())
	{
		throw invalid_argument("invalid output file");
	}

	outputFile << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)" << endl;
	outputFile << m_outputSvg.str() << endl;
	outputFile << R"(</svg>)" << endl;
	outputFile.close();
}

void SVGCanvas::SetColor(Color color)
{
	m_currentColor = color;
}

void SVGCanvas::MoveTo(double x, double y)
{
	m_drawPoint = { x, y };
}

void SVGCanvas::LineTo(double x, double y)
{
	string svgLine =
		R"(<line x1=")" + to_string(m_drawPoint.m_x) + R"(" )"
		+ R"(y1=")" + to_string(m_drawPoint.m_y) + R"(" )"
		+ R"(x2=")" + to_string(x) + R"(" )"
		+ R"(y2=")" + to_string(y) + R"(" )"
		+ R"(style="stroke:)" + m_currentColor
		+ R"(;stroke-width:)" + to_string(STROKE_WIDTH) + R"(" />)";
	m_outputSvg << svgLine << endl;
}

void SVGCanvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	string svgEllipse =
		R"(<ellipse cx=")" + to_string(cx) + R"(" )"
		+ R"(cy=")" + to_string(cy) + R"(" )"
		+ R"(rx=")" + to_string(rx) + R"(" )"
		+ R"(ry=")" + to_string(ry) + R"(" )"
		+ R"(style="stroke:)" + m_currentColor
		+ R"(;stroke-width:)" + to_string(STROKE_WIDTH) + R"(; fill:none;" />)";
	m_outputSvg << svgEllipse << endl;
}

void SVGCanvas::DrawText(double x, double y, double fontSize, string const& text)
{
	string svgText =
		R"(<text x=")" + to_string(x) + R"(" )"
		+ R"(y=")" + to_string(y) + R"(" )"
		+ R"(font-size=")" + to_string(fontSize) + R"(" )"
		+ R"(fill=")" + m_currentColor + R"(">)"
		+ text + R"(</text>)";
	m_outputSvg << svgText << endl;
}