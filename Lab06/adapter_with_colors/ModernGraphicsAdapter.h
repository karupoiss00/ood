#pragma once
#include "modern_graphics_lib.h"
#include "graphics_lib.h"
#include "shape_drawing_lib.h"

class ModernGraphicsAdapter : public graphics_lib_pro::ICanvas
{
public:
	ModernGraphicsAdapter() = delete;
	ModernGraphicsAdapter(modern_graphics_lib_pro::CModernGraphicsRenderer& modernRenderer)
		: m_renderer(modernRenderer)
		, m_startPoint(0, 0)
		, m_color(0, 0, 0, 1)
	{}

	void MoveTo(int x, int y) override
	{
		m_startPoint = { x, y };
	}
	void LineTo(int x, int y) override
	{
		const modern_graphics_lib_pro::CPoint end(x, y);

		m_renderer.DrawLine(m_startPoint, end, m_color);

		m_startPoint = end;
	}

	void SetColor(uint32_t hexColor) override {
		m_color = {
			static_cast<float>(((hexColor >> 16) & 0xFF) / 255.0),
			static_cast<float>(((hexColor >> 8) & 0xFF) / 255.0),
			static_cast<float>((hexColor & 0xFF) / 255.0),
			1
		};
	}

private:
	modern_graphics_lib_pro::CPoint m_startPoint;
	modern_graphics_lib_pro::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib_pro::CRGBAColor m_color;
};