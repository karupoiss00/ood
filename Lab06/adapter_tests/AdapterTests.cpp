#include <sstream>
#include <string>
#include <catch2/catch.hpp>

#include "modern_graphics_lib.h"
#include "graphics_lib.h"
#include "ModernGraphicsClassAdapter.h"
#include "ModernGraphicsAdapter.h"

using namespace std;
namespace mgl = modern_graphics_lib;
namespace gl = graphics_lib;

string DrawWithoutAdapters(const vector<mgl::CPoint>& points)
{
	stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);

	const auto first = points.begin();
	renderer.BeginDraw();

	for (auto it = first; it != points.end(); ++it)
	{
		if (it + 1 != points.end())
		{
			renderer.DrawLine(*it, *(it + 1));
		}
		else
		{
			renderer.DrawLine(*it, *first);
		}
	}

	renderer.EndDraw();

	return strm.str();
}

void DrawWithAdapter(mgl::CModernGraphicsRenderer& renderer, graphics_lib::ICanvas& adapter, const vector<mgl::CPoint>& points)
{
	renderer.BeginDraw();

	auto first = points.begin();
	adapter.MoveTo((*first).x, (*first).y);

	for (auto it = first + 1; it != points.end(); ++it)
	{
		adapter.LineTo((*it).x, (*it).y);
	}

	adapter.LineTo((*first).x, (*first).y);
	renderer.EndDraw();
}

string DrawWithObjectAdapter(const vector<mgl::CPoint>& points)
{
	stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	ModernGraphicsAdapter adapter(renderer);

	DrawWithAdapter(renderer, adapter, points);

	return strm.str();
}

string DrawShapeWithClassAdapter(const vector<mgl::CPoint>& points)
{
	stringstream strm;
	ModernGraphicsClassAdapter adapter(strm);

	DrawWithAdapter(adapter, adapter, points);

	return strm.str();
}

TEST_CASE("check object adapter interface implementation")
{
	stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	ModernGraphicsAdapter adapter(renderer);
	
	static_cast<graphics_lib::ICanvas*>(&adapter);
}

TEST_CASE("draw triangle with object adapter")
{
	auto triangle = {
		mgl::CPoint(10, 15),
		mgl::CPoint(100, 200),
		mgl::CPoint(150, 250),
	};

	const auto originalShape = DrawWithoutAdapters(triangle);
	const auto withAdapterShape = DrawWithObjectAdapter(triangle);

	REQUIRE(originalShape == withAdapterShape);
}

TEST_CASE("check class adapter interface implementation")
{
	stringstream strm;
	ModernGraphicsClassAdapter adapter(strm);

	static_cast<graphics_lib::ICanvas*>(&adapter);
	static_cast<mgl::CModernGraphicsRenderer*>(&adapter);
}

TEST_CASE("draw triangle with class adapter")
{
	auto triangle = {
		mgl::CPoint(10, 15),
		mgl::CPoint(100, 200),
		mgl::CPoint(150, 250),
	};

	const auto originalShape = DrawWithoutAdapters(triangle);
	const auto withAdapterShape = DrawShapeWithClassAdapter(triangle);

	REQUIRE(originalShape == withAdapterShape);
}