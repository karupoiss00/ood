#include <iostream>
#include <string>
#include <sstream>
#include "PictureController.h"
#include "ShapeStrategyFactory.h"

using namespace std;
using namespace shapes;
using namespace std::placeholders;
using namespace gfx;

PictureController::PictureController(Picture& picture, ICanvas& canvas, std::istream& input, std::ostream& output)
	: m_input(input), m_output(output), m_canvas(canvas), m_picture(picture)
{
	m_commandMap.emplace("AddShape", bind(&PictureController::HandleAddShape, this, _1));
	m_commandMap.emplace("MoveShape", bind(&PictureController::HandleMoveShape, this, _1));
	m_commandMap.emplace("MovePicture", bind(&PictureController::HandleMovePicture, this, _1));
	m_commandMap.emplace("DeleteShape", bind(&PictureController::HandleDeleteShape, this, _1));
	m_commandMap.emplace("ChangeColor", bind(&PictureController::HandleChangeColor, this, _1));
	m_commandMap.emplace("ChangeShape", bind(&PictureController::HandleChangeShape, this, _1));
	m_commandMap.emplace("DrawShape", bind(&PictureController::HandleDrawShape, this, _1));
	m_commandMap.emplace("DrawPicture", bind(&PictureController::HandleDrawPicture, this, _1));
	m_commandMap.emplace("List", bind(&PictureController::HandleList, this, _1));
}

bool PictureController::HandleCommand()
{
	string commandLine;

	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_commandMap.find(action);

	if (it != m_commandMap.end())
	{
		it->second(strm);

		return true;
	}

	return false;
}

void PictureController::HandleAddShape(std::istream& input)
{
	string id, color;

	input >> id >> color;

	if (id.empty() || !IsValidHexColor(color))
	{
		throw invalid_argument("invalid command arguments, template: <id> <hex color> <shape type> <shape args>");
	}

	try
	{
		auto strategy = ShapeStrategyFactory::CreateFromStream(input);
		m_picture.AddShape(id, color, move(strategy));
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}
}

void PictureController::HandleChangeShape(std::istream& input)
{
	string id;

	input >> id;

	if (id.empty())
	{
		throw invalid_argument("invalid command arguments, template: <id> <shape type> <shape args>");
	}

	try
	{
		auto strategy = ShapeStrategyFactory::CreateFromStream(input);
		m_picture.GetShapeById(id)->SetShapeStrategy(move(strategy));
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}
}

void PictureController::HandleChangeColor(std::istream& input)
{
	string id, color;

	input >> id >> color;

	if (id.empty() || !IsValidHexColor(color))
	{
		throw invalid_argument("invalid command arguments, template: <id> <hex color>");
	}

	m_picture.GetShapeById(id)->SetColor(color);
}

void PictureController::HandleMoveShape(std::istream& input)
{
	string id, dxStr, dyStr;

	input >> id >> dxStr >> dyStr;

	if (id.empty() || dxStr.empty() || dyStr.empty())
	{
		throw invalid_argument("invalid command arguments, template: <id> <delta x> <delta y>");
	}

	try
	{
		double dx = stod(dxStr);
		double dy = stod(dyStr);
		m_picture.GetShapeById(id)->Move(dx, dy);
	}
	catch (...)
	{
		throw invalid_argument("can not parse numbers from arguments");
	}
}

void PictureController::HandleMovePicture(std::istream& input)
{
	string dxStr, dyStr;

	input >> dxStr >> dyStr;

	if (dxStr.empty() || dyStr.empty())
	{
		throw invalid_argument("invalid command arguments, template: <delta x> <delta y>");
	}

	try
	{
		double dx = stod(dxStr);
		double dy = stod(dyStr);
		m_picture.MovePicture(dx, dy);
	}
	catch (...)
	{
		throw invalid_argument("can not parse numbers from arguments");
	}
}

void PictureController::HandleDeleteShape(std::istream& input)
{
	string id;

	input >> id;

	if (id.empty())
	{
		throw invalid_argument("invalid command arguments, template: <id>");
	}

	m_picture.DeleteShape(id);
}

void PictureController::HandleList(std::istream& input)
{
	for (auto const& shapeInfo : m_picture.List())
	{
		m_output << shapeInfo << endl;
	}
}

void PictureController::HandleDrawPicture(std::istream& input)
{
	m_picture.Draw(m_canvas);
}

void PictureController::HandleDrawShape(std::istream& input)
{
	string id;

	input >> id;

	if (id.empty())
	{
		throw invalid_argument("invalid command arguments, template: <id>");
	}

	m_picture.GetShapeById(id)->Draw(m_canvas);
}
