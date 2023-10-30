#pragma once
#include <array>
#include "graphics_lib.h"

namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib_pro::ICanvas& canvas) const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CShape : public ICanvasDrawable
	{
	public:
		CShape()
			: m_color(0)
		{}

		CShape(uint32_t rgbColor)
			: m_color(rgbColor)
		{}

		void SetColor(uint32_t rgbColor)
		{
			m_color = rgbColor;
		}

		void Draw(graphics_lib_pro::ICanvas& canvas) const override
		{
			canvas.SetColor(m_color);
		}
	private:
		uint32_t m_color;
	};

	class CTriangle : public CShape
	{
	public:
		CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t color)
			: CShape(color)
		{
			m_vertexes = { p1, p2, p3 };
		}

		void Draw(graphics_lib_pro::ICanvas& canvas) const override
		{
			CShape::Draw(canvas);
			canvas.MoveTo(m_vertexes[0].x, m_vertexes[0].y);
			canvas.LineTo(m_vertexes[1].x, m_vertexes[1].y);
			canvas.MoveTo(m_vertexes[1].x, m_vertexes[1].y);
			canvas.LineTo(m_vertexes[2].x, m_vertexes[2].y);
			canvas.MoveTo(m_vertexes[2].x, m_vertexes[2].y);
			canvas.LineTo(m_vertexes[0].x, m_vertexes[0].y);
		}

	private:
		std::array<Point, 3> m_vertexes;
	};

	class CRectangle : public CShape
	{
	public:
		CRectangle(const Point& leftTop, int width, int height, uint32_t color)
			: CShape(color) 
			, m_topLeft(leftTop)
			, m_width(width)
			, m_height(height)
		{}

		void Draw(graphics_lib_pro::ICanvas& canvas) const override
		{
			CShape::Draw(canvas);
			canvas.MoveTo(m_topLeft.x, m_topLeft.y);
			canvas.LineTo(m_topLeft.x, m_topLeft.y + m_height);
			canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y);

			canvas.MoveTo(m_topLeft.x + m_width, m_topLeft.y + m_height);
			canvas.LineTo(m_topLeft.x, m_topLeft.y + m_height);
			canvas.LineTo(m_topLeft.x + m_width, m_topLeft.y);
		}

	private:
		Point m_topLeft;
		int m_width;
		int m_height;
	};

	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib_pro::ICanvas& canvas)
			: m_canvas(canvas)
		{}
		void Draw(const ICanvasDrawable& drawable)
		{
			drawable.Draw(m_canvas);
		}

	private:
		graphics_lib_pro::ICanvas& m_canvas;
	};
}