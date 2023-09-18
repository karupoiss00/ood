#include <sstream>
#include "ICanvas.h"
#include "Point.h"

class SVGCanvas : public sfx::ICanvas
{
public:
	explicit SVGCanvas() = delete;
	SVGCanvas(std::string const& fileName);

	/*virtual void MoveTo(double x, double y) = 0;
	virtual void SetColor(Color color) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
	virtual void DrawText(double x, double y, std::string const& text) = 0;*/

	void SetColor(sfx::Color color) override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double x, double y, double fontSize, std::string const& text) override;

	void Save();
private:
	sfx::Color m_currentColor;
	Point m_drawPoint;
	std::stringstream m_outputSvg;
	std::string m_outputFileName;
};