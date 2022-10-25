#include <fstream>
#include "SVGCanvas.h"

using namespace std;

SVGCanvas::SVGCanvas(std::string const& fileName)
	: m_outputFileName(fileName), m_currentColor(Color::BLACK), m_strokeWidth(4)
{
	ofstream outputFile(fileName);

	if (!outputFile.good())
	{
		throw invalid_argument("invalid output file");
	}

	outputFile.close();

	m_outputSvg = stringstream("");
}

void SVGCanvas::Save()
{
	ofstream outputFile(m_outputFileName, std::ofstream::trunc);

	if (!outputFile.good())
	{
		throw invalid_argument("invalid output file");
	}

	string line;

	outputFile << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)" << endl;

	while (getline(m_outputSvg, line))
	{
		outputFile << line << endl;
	}

	outputFile << R"(</svg>)" << endl;
	outputFile.close();

	m_outputSvg.clear();
	m_outputSvg.seekg(0);
}

void SVGCanvas::SetStrokeWidth(size_t width)
{
	m_strokeWidth = width;
}

void SVGCanvas::SetColor(Color color)
{
	m_currentColor = color;
}

void SVGCanvas::DrawLine(Vec2 from, Vec2 to)
{
	string svgLine = 
		R"(<line x1=")" + to_string(from.x) + R"(" )"
		+ R"(y1=")" + to_string(from.y) + R"(" )"
		+ R"(x2=")" + to_string(to.x) + R"(" )"
		+ R"(y2=")" + to_string(to.y) + R"(" )"
		+ R"(style="stroke:)" + ColorToString(m_currentColor) 
		+ R"(;stroke-width:)" + to_string(m_strokeWidth) + R"(" />)";
	m_outputSvg << svgLine << endl;

	Save();
}

void SVGCanvas::DrawEllipse(Vec2 topLeft, unsigned width, unsigned height)
{
	int rx = width / 2;
	int ry = height / 2;
	int cx = topLeft.x + rx;
	int cy = topLeft.y + ry;

	string svgLine =
		R"(<ellipse cx=")" + to_string(cx) + R"(" )"
		+ R"(cy=")" + to_string(cy) + R"(" )"
		+ R"(rx=")" + to_string(rx) + R"(" )"
		+ R"(ry=")" + to_string(ry) + R"(" )"
		+ R"(fill="#FFAABB" />)";

	m_outputSvg << svgLine << endl;

	Save();
}