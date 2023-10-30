#pragma once
#include <ostream>
#include <format>

namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y)
			: x(x)
			, y(y)
		{
		}

		int x;
		int y;
	};

	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{
		}
		float r, g, b, a;
	};


	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream& strm)
			: m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing)
			{
				EndDraw();
			}
		}

		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
		{
			if (!m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}

			const auto colorTag = std::format(
				R"(<color r="{}" g="{}" b="{}" a="{}" />)",
				color.r, color.g, color.b, color.a
			);
			m_out << std::format(R"(  
	<line fromX="{}" fromY="{}" toX="{}" toY="{}">
		{}
	</line>)", start.x, start.y, end.x, end.y, colorTag) << std::endl;

		}

		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}

	private:
		std::ostream& m_out;
		bool m_drawing = false;
	};
} // namespace modern_graphics_lib_pro
