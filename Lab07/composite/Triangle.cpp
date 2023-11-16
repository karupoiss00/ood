#include <algorithm>
#include "Triangle.h"

using namespace std;

CTriangle::CTriangle(std::array<PointD, 3> vertexes, shared_ptr<CLineStyle> const& outlineStyle, shared_ptr<CColorStyle> const& fillStyle)
	: CShape(outlineStyle, fillStyle)
	, m_vertexes(vertexes)
{
	array<double, 3> xCoords;
	std::transform(
		vertexes.begin(),
		vertexes.end(), 
		xCoords.begin(), 
		[](auto const& point) {
			return point.x;
		}
	);
	array<double, 3> yCoords;
	std::transform(
		vertexes.begin(),
		vertexes.end(),
		yCoords.begin(),
		[](auto const& point) {
			return point.y;
		});
	m_left = *min_element(xCoords.begin(), xCoords.end());
	m_top = *min_element(yCoords.begin(), yCoords.end());
	m_width = *max_element(xCoords.begin(), xCoords.end()) - m_left;
	m_height = *max_element(yCoords.begin(), yCoords.end()) - m_top;
}

RectD CTriangle::GetFrameImpl()
{
	return { m_left, m_top, m_width, m_height };
}

void CTriangle::SetFrameImpl(double offsetLeft, double offsetTop, double scaleWidth, double scaleHeight)
{
	m_left += offsetLeft;
	m_top += offsetTop;
	m_width *= scaleWidth;
	m_height *= scaleHeight;

	for (auto& vertex : m_vertexes)
	{
		vertex.x += offsetLeft;
		vertex.y += offsetTop;
	}
}

void CTriangle::DrawImpl(ICanvas& canvas) const
{
	canvas.MoveTo(m_vertexes[0].x, m_vertexes[0].y);
	canvas.LineTo(m_vertexes[1].x, m_vertexes[1].y);

	canvas.MoveTo(m_vertexes[1].x, m_vertexes[1].y);
	canvas.LineTo(m_vertexes[2].x, m_vertexes[2].y);

	canvas.MoveTo(m_vertexes[2].x, m_vertexes[2].y);
	canvas.LineTo(m_vertexes[0].x, m_vertexes[0].y);
}
