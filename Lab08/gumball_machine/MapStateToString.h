#pragma once

#include <map>
#include <string>

enum class State : size_t
{
	SOLD_OUT,
	NO_QUARTER,
	HAS_QUARTER,
	SOLD
};

const std::map<State, std::string> STATE_STRING_MAP = {
	{ State::SOLD_OUT, "sold out" },
	{ State::SOLD, "delivering a gumball" },
	{ State::NO_QUARTER, "waiting for quarter" },
	{ State::HAS_QUARTER, "waiting for turn of crank" },
};