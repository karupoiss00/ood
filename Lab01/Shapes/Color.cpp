#include "Color.h"

using namespace std;

constexpr string_view HEX_COLOR_REGEX = "^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$";

bool gfx::IsValidHexColor(std::string const& str)
{
	const regex pattern(HEX_COLOR_REGEX.data());

	return regex_match(str, pattern);
}

void gfx::VerifyHexColor(std::string const& str)
{
	if (IsValidHexColor(str))
	{
		throw std::exception("invalid hex color format");
	}
}
