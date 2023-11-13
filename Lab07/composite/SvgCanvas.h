#pragma once
#include <optional>
#include <vector>
#include <iostream>
#include <sstream>

#include "CommonTypes.h"
#include "ICanvas.h"

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(double width, double height, std::stringstream& strm);

	void SetLineWidth(unsigned width) override;
	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;

	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;

	void DrawEllipse(double left, double top, double width, double height) override;

	void Save();
private:
	void AddOutlineColor();
	void FillFigure();
	void FillVertexesArea();

	std::string ColorToString(RGBAColor color);

	PointD m_startPoint;

	double m_width;
	double m_height;
	unsigned m_strokeWidth;

	std::stringstream& m_strm;
	std::streampos m_fillPos;

	std::optional<RGBAColor> m_outlineColor;
	std::optional<RGBAColor> m_fillColor;

	std::vector<PointD> m_fillAreaVertexes;
};