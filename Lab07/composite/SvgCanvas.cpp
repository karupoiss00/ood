#include <format>
#include "SvgCanvas.h"

using namespace std;

CSvgCanvas::CSvgCanvas(double width, double height, stringstream& strm)
	: m_startPoint({ 0, 0 })
	, m_width(width)
	, m_height(height)
	, m_strokeWidth(1)
	, m_strm(strm)
{
	m_strm.str("");
	m_strm << "<body>" << endl;
	m_strm << format(R"(  <svg width="{}" height="{}">)", m_width, m_height) << endl;
}

void CSvgCanvas::Save() {
	m_strm << "  </svg>" << endl
		   << "</body>" << endl;
}

void CSvgCanvas::SetLineColor(RGBAColor color)
{
	m_outlineColor = color;
}

void CSvgCanvas::SetLineWidth(unsigned width)
{
	m_strokeWidth = width;
}

void CSvgCanvas::BeginFill(RGBAColor color)
{
	m_fillColor = color;
	m_fillPos = m_strm.tellp();
}

void CSvgCanvas::EndFill()
{
	FillVertexesArea();
	m_fillAreaVertexes = {};
	m_fillColor = nullopt;
}

void CSvgCanvas::DrawEllipse(double left, double top, double width, double height)
{
	double rx = width / 2;
	double ry = height / 2;
	double cx = left + rx;
	double cy = top + ry;

	m_strm << format(R"(    <ellipse cx="{}" cy="{}" rx="{}" ry="{}" )", cx, cy, rx, ry);
	
	FillFigure();
	AddOutlineColor();

	m_strm << "/>" << endl;
}

void CSvgCanvas::MoveTo(double x, double y)
{
	m_startPoint = { x, y };
}

void CSvgCanvas::LineTo(double x, double y)
{
	m_strm << format(R"(    <line x1="{}" y1="{}" x2="{}" y2="{}"" )", m_startPoint.x, m_startPoint.y, x, y);
	AddOutlineColor();
	m_strm << "/>" << endl;


	if (m_fillColor.has_value())
	{
		m_fillAreaVertexes.push_back(m_startPoint);
		m_fillAreaVertexes.push_back({ x, y });
	}
}

void CSvgCanvas::AddOutlineColor()
{
	if (m_outlineColor)
	{
		auto color = m_outlineColor.value();
		m_strm << format(R"( stroke={} stroke-width="{}")", ColorToString(color), m_strokeWidth);
	}
}

void CSvgCanvas::FillVertexesArea()
{
	if (m_fillAreaVertexes.empty() || !m_fillColor.has_value())
	{
		return;
	}

	auto color = m_fillColor.value();
	string lines = m_strm.str().substr(static_cast<unsigned>(m_fillPos));

	m_strm.seekp(m_fillPos, ios::beg);

	m_strm << format(R"(    <path d="M {} {})", m_fillAreaVertexes[0].x, m_fillAreaVertexes[0].y);

	for (size_t i = 1; i < m_fillAreaVertexes.size(); ++i)
	{
		m_strm << format(R"( L {} {})", m_fillAreaVertexes[i].x, m_fillAreaVertexes[i].y);
	}

	m_strm << " Z\"";
	m_strm << format(R"( fill={})", ColorToString(color));
	m_strm << "/>" << endl;
	m_strm << lines;
}


void CSvgCanvas::FillFigure()
{
	if (m_fillColor.has_value())
	{
		auto color = *m_fillColor;
		m_strm << format(R"( fill={})", ColorToString(color));
	
	}
	else
	{
		m_strm << " fill=\"transparent\"";
	}
}

std::string CSvgCanvas::ColorToString(RGBAColor color)
{
	return format(R"("rgb{}{}, {}, {}{}")", '(', (color >> 16 & 255), (color >> 8 & 255), (color & 255), ')');
}