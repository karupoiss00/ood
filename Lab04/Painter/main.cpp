#include <iostream>
#include "Designer.h"
#include "Painter.h"
#include "PictureDraft.h"
#include "ShapeFactory.h"
#include "SVGCanvas.h"

using namespace std;

int main()
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPictureDraft draft = designer.CreateDraft(cin);
	SVGCanvas canvas("image.svg");
	CPainter painter;
	painter.DrawPicture(draft, canvas);

	return 0;
}