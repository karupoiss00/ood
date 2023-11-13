#include <cstdint>
#include <optional>
#include <memory>
#include <limits>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <fstream>

#include "Slide.h"
#include "ShapeGroup.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "SvgCanvas.h"
#include "ColorStyle.h"

using namespace std;

shared_ptr<ISlide> CreateSlideExample();
void MoveAndResizeExample(const shared_ptr<ISlide>& slide);
void DrawSlideToFile(const shared_ptr<ISlide>& slide, const string& filename);

int main()
{
	auto slide = CreateSlideExample();
	DrawSlideToFile(slide, "slide1.html");

	MoveAndResizeExample(slide);
	DrawSlideToFile(slide, "slide2.html");

	return 0;
}

shared_ptr<ISlide> CreateSlideExample()
{
	auto slide = make_shared<CSlide>();
	auto& shapes = slide->GetShapes();

	auto group = make_shared<CShapeGroup>();

	group->InsertShape(make_shared<CRectangle>(RectD(100, 100, 200, 200), make_shared<CLineStyle>(2, 0XAF7632), make_shared<CColorStyle>(0X006EAA)));
	group->InsertShape(make_shared<CRectangle>(RectD(150, 150, 200, 200), make_shared<CLineStyle>(3, 0XAF7632), make_shared<CColorStyle>(0X00A36A)));
	group->InsertShape(make_shared<CRectangle>(RectD(200, 200, 200, 200), make_shared<CLineStyle>(4, 0X006EAA), make_shared<CColorStyle>(0XAF7632)));
	group->InsertShape(make_shared<CEllipse>(RectD(200, 200, 200, 200), make_shared<CLineStyle>(5, 0X006EAA), make_shared<CColorStyle>(0XAD2432)));

	shapes.InsertShape(group);

	return slide;
}

void MoveAndResizeExample(const shared_ptr<ISlide>& slide)
{
	auto& shapes = slide->GetShapes();
	auto group = shapes.GetShapeAtIndex(0);

	group->SetFrame({ 300, 300, 150, 150 });
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
		throw logic_error("An error occurred when writing file");
	}
}