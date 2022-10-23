#include "Painter.h"

void CPainter::DrawPicture(CPictureDraft const& draft, ICanvas& canvas) const
{
	for (auto shape = draft.begin(); shape != draft.end(); shape++)
	{
		shape->Draw(canvas);
	}
}