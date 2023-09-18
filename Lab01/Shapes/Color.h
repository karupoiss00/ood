#pragma once
#include <string>
#include <regex>

namespace sfx
{
	using Color = std::string;
	bool IsValidHexColor(std::string const& str);
	void VerifyHexColor(std::string const& str);
}