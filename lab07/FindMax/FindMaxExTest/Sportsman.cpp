#include "stdafx.h"
#include "Sportsman.h"

Sportsman::Sportsman(std::string const& lfm, int growth, int weight)
	: lfm(lfm)
	, growth(growth)
	, weight(weight)
{
}

bool Sportsman::operator<(Sportsman const& other)
{
	return lfm < other.lfm;
}

bool Sportsman::operator==(const Sportsman& other)
{
	return lfm == other.lfm && growth == other.growth && weight == other.weight;
}
