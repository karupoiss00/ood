#pragma once
#include <iostream>
#include <map>
#include <functional>

#include "ICanvas.h"
#include "Picture.h"

class PictureController
{
public:
	PictureController(shapes::Picture& picture, ICanvas& canvas, std::istream& input, std::ostream& output);
	bool HandleCommand();
private:
	void HandleAddShape(std::istream& input);
	void HandleChangeShape(std::istream& input);
	void HandleChangeColor(std::istream& input);
	void HandleMoveShape(std::istream& input);
	void HandleMovePicture(std::istream& input);
	void HandleDeleteShape(std::istream& input);
	void HandleList(std::istream& input);
	void HandleDrawPicture(std::istream& input);
	void HandleDrawShape(std::istream& input);

	using CommandMap = std::map<std::string, std::function<void(std::istream& args)>>;

	std::istream& m_input;
	std::ostream& m_output;
	shapes::Picture& m_picture;
	CommandMap m_commandMap;
	ICanvas& m_canvas;
};