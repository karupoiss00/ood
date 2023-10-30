#include <catch2/catch.hpp>
#include <sstream>
#include <string>

#include "ModernGraphicsAdapter.h"

using namespace std;
namespace mgl = modern_graphics_lib_pro;
namespace gl = graphics_lib_pro;

string DrawWithoutAdapters(const vector<mgl::CPoint>& points, mgl::CRGBAColor const& color)
{
	stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);

	const auto first = points.begin();
	renderer.BeginDraw();

	for (auto it = first; it != points.end(); ++it)
	{
		if (it + 1 != points.end())
		{
			renderer.DrawLine(*it, *(it + 1), color);
		}
		else
		{
			renderer.DrawLine(*it, *first, color);
		}
	}

	renderer.EndDraw();

	return strm.str();
}

void DrawWithAdapter(mgl::CModernGraphicsRenderer& renderer, gl::ICanvas& adapter, const vector<mgl::CPoint>& points, uint32_t color)
{
	renderer.BeginDraw();
	adapter.SetColor(color);
	auto first = points.begin();
	adapter.MoveTo((*first).x, (*first).y);

	for (auto it = first + 1; it != points.end(); ++it)
	{
		adapter.LineTo((*it).x, (*it).y);
	}

	adapter.LineTo((*first).x, (*first).y);
	renderer.EndDraw();
}

string DrawWithObjectAdapter(const vector<mgl::CPoint>& points, uint32_t color)
{
	stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	ModernGraphicsAdapter adapter(renderer);

	DrawWithAdapter(renderer, adapter, points, color);

	return strm.str();
}

TEST_CASE("check object adapter interface implementation")
{
	stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	ModernGraphicsAdapter adapter(renderer);

	static_cast<graphics_lib_pro::ICanvas*>(&adapter);
}

TEST_CASE("draw triangle with object adapter")
{
	auto triangle = {
		mgl::CPoint(10, 15),
		mgl::CPoint(100, 200),
		mgl::CPoint(150, 250),
	};
	const uint32_t colorAsNumber = 4013373;
	const mgl::CRGBAColor color(0.23921569, 0.23921569, 0.23921569, 1.0);
	const auto originalShape = DrawWithoutAdapters(triangle, color);
	const auto withAdapterShape = DrawWithObjectAdapter(triangle, colorAsNumber);

	REQUIRE(originalShape == withAdapterShape);
}