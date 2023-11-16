#include <cstdint>
#include <optional>
#include <memory>
#include <limits>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <random>

#include "Slide.h"
#include "ShapeGroup.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "SvgCanvas.h"
#include "ColorStyle.h"

using namespace std;

shared_ptr<ISlide> CreateSlideExample();
void MoveAndResizeExample(const shared_ptr<ISlide>& slide);
void DrawSlideToFile(const shared_ptr<ISlide>& slide, const string& filename);

int main()
{
	auto slide = CreateSlideExample();
	DrawSlideToFile(slide, "slide.html");

	MoveAndResizeExample(slide);
	DrawSlideToFile(slide, "slide_modified.html");

	return 0;
}

shared_ptr<ISlide> CreateSlideExample()
{
	int startValue = 0;
	int shapesCount = 10;

	auto slide = make_shared<CSlide>();
	auto& shapes = slide->GetShapes();

	auto group = make_shared<CShapeGroup>();

	for (int i = startValue; i < startValue + shapesCount; i++)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> color(0, 0xFFFFFF); // distribution in range [1, 6]

		auto rect = RectD(i * 10, i * i * 10, 10 * i, 10 * i);

		if (i % 2 == 0)
		{
			group->InsertShape(make_shared<CRectangle>(rect, make_shared<CLineStyle>(abs(i), color(rng)), make_shared<CColorStyle>(color(rng))));	
		}
		else if (i % 3 != 0)
		{
			array<PointD, 3> points = {
				PointD(i * 10, i * i * 10),
				PointD(i * 10 + 20, i * i * 10 + 25),
				PointD(i * 10 + 100, i * i * 10 + 25),
			};
	
			group->InsertShape(make_shared<CTriangle>(points, make_shared<CLineStyle>(abs(i), color(rng)), make_shared<CColorStyle>(color(rng))));
		}
		else
		{
			group->InsertShape(make_shared<CEllipse>(rect, make_shared<CLineStyle>(abs(i), color(rng)), make_shared<CColorStyle>(color(rng))));
		}
	}

	shapes.InsertShape(group);

	return slide;
}

void MoveAndResizeExample(const shared_ptr<ISlide>& slide)
{
	auto& shapes = slide->GetShapes();
	auto group = shapes.GetShapeAtIndex(0);

	group->SetFrame({ 100, 100, 720, 720 });
}

void DrawSlideToFile(const shared_ptr<ISlide>& slide, const string& filename)
{
	stringstream strm;
	CSvgCanvas canvas(slide->GetWidth(), slide->GetHeight(), strm);

	slide->Draw(canvas);

	canvas.Save();

	ofstream outputFile(filename.c_str());

	if (outputFile.is_open())
	{
		outputFile << strm.str();
	}
	else
	{
		throw logic_error("File writing error");
	}
}