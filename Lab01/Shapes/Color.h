#pragma once
#include <string>
#include <regex>

namespace gfx
{
	using Color = std::string;
	bool IsValidHexColor(std::string const& str);
	void VerifyHexColor(std::string const& str);
}