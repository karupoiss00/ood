#include <catch2/catch.hpp>
#include <catch2jest/catch2jest.hpp>
#include <optional>

#include "Ellipse.h"
#include "ShapeGroup.h"
#include "Rectangle.h"
#include "ColorStyle.h"
#include "LineStyle.h"

using namespace std;

struct EmptyGroupShapeFixture
{
	EmptyGroupShapeFixture()
		: group(make_shared<CShapeGroup>())
	{
	}

	shared_ptr<CShapeGroup> group;
};

struct CMockCanvas : ICanvas
{
	void SetLineWidth(unsigned width) override {};
	void SetLineColor(RGBAColor color) override {};
	void BeginFill(RGBAColor color) override {};
	void EndFill() override {};
	void MoveTo(double x, double y) override {};

	void DrawEllipse(double left, double top, double width, double height) override
	{
		++callDrawCount;
	}

	void LineTo(double x, double y) override
	{
		++callDrawCount;
	}

	size_t callDrawCount = 0;
};

TEST_CASE_METHOD(EmptyGroupShapeFixture, "empty shape group")
{
	SECTION("has no shapes after creation")
	{
		REQUIRE(group->GetShapesCount() == 0);
	}

	SECTION("has zero frame")
	{
		REQUIRE(group->GetFrame() == RectD(0, 0, 0, 0));
	}

	SECTION("ignore set frame") 
	{
		group->SetFrame({ 100, 100, 300, 300 });
		REQUIRE(group->GetFrame() == RectD(0, 0, 0, 0));
	}

	SECTION("return not null pointer")
	{
		auto self = group->GetGroup();
		REQUIRE(self.get() != nullptr);
	}

	SECTION("throws an exception when trying to get a shape by index")
	{
		REQUIRE_THROWS_AS(group->GetShapeAtIndex(0), std::out_of_range);
	}

	SECTION("has an undefined state of all properties")
	{
		auto style = group->GetOutlineStyle();

		REQUIRE(style->IsEnabled() == nullopt);
		REQUIRE(style->GetColor() == nullopt);
	}
	
	SECTION("has an undefined state of all properties")
	{
		auto style = group->GetFillStyle();

		REQUIRE(style->IsEnabled() == nullopt);
		REQUIRE(style->GetColor() == nullopt);
	}

	SECTION("allows insert and remove shapes")
	{
		group->InsertShape(make_shared<CRectangle>(RectD(100, 100, 200, 200), make_shared<CLineStyle>(1, 0x000000), make_shared<CColorStyle>(0XDEADBE)));
		REQUIRE(group->GetShapesCount() == 1);
		
		group->RemoveShapeAtIndex(0);
		REQUIRE(group->GetShapesCount() == 0);
	}
}

struct GroupShapeFixture : EmptyGroupShapeFixture
{
	GroupShapeFixture()
	{
		group->InsertShape(make_shared<CRectangle>(RectD(100, 100, 200, 200), make_shared<CLineStyle>(4, 0X006EAA), make_shared<CColorStyle>(0XAF7632)));
		group->InsertShape(make_shared<CEllipse>(RectD(200, 200, 200, 200), make_shared<CLineStyle>(5, 0X006EAA), make_shared<CColorStyle>(0XAD2432)));
	}
};

TEST_CASE_METHOD(GroupShapeFixture, "not empty shape group")
{
	SECTION("returns a frame considering all shapes")
	{
		REQUIRE(group->GetFrame() == RectD(100, 100, 300, 300));
	}

	SECTION("group has not style if childs has different it")
	{
		REQUIRE(!group->GetFillStyle()->GetColor().has_value());

		group->GetFillStyle()->SetColor(0XAF7632);

		REQUIRE(group->GetFillStyle()->GetColor().has_value());
		REQUIRE(*(group->GetFillStyle()->GetColor()) == 0XAF7632);
	}

	SECTION("empty group not affecting on rect")
	{
		group->InsertShape(make_shared<CShapeGroup>());
		REQUIRE(group->GetFrame() == RectD(100, 100, 300, 300));
	}

	SECTION("setting the frame of group changes the frames of all shapes")
	{
		group->SetFrame({ 200, 200, 150, 150 });
		REQUIRE(group->GetFrame() == RectD(200, 200, 150, 150));

		REQUIRE(group->GetShapeAtIndex(0)->GetFrame() == RectD(200, 200, 100, 100));
		REQUIRE(group->GetShapeAtIndex(1)->GetFrame() == RectD(250, 250, 100, 100));
	}

	SECTION("inserts a shape in the specified position")
	{
		auto shape = make_shared<CEllipse>(RectD(300, 300, 200, 200), make_shared<CLineStyle>(1, 0x000000), make_shared<CColorStyle>(0XBEEFDE));
		group->InsertShape(shape, 1);

		REQUIRE(group->GetShapesCount() == 3);
		REQUIRE(group->GetShapeAtIndex(1).get() == shape.get());
	}

	SECTION("draws each shape on canvas")
	{
		CMockCanvas canvas;
		group->Draw(canvas);

		REQUIRE(canvas.callDrawCount == 5);
	}

	SECTION("returns pointer to self")
	{
		auto self = group->GetGroup();

		auto shape = make_shared<CEllipse>(RectD(300, 300, 200, 200), make_shared<CLineStyle>(1, 0x000000), make_shared<CColorStyle>(0XBEEFDE));
		self->InsertShape(shape);


		REQUIRE(self->GetShapesCount() == group->GetShapesCount());
	}
}