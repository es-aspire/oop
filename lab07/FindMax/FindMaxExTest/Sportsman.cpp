#include "stdafx.h"
#include "Sportsman.h"

Sportsman::Sportsman(std::string const& name, int growth, int weight)
	: name(name)
	, growth(growth)
	, weight(weight)
{
}

bool Sportsman::operator==(const Sportsman& other)
{
	return name == other.name && growth == other.growth && weight == other.weight;
}

bool operator<(Sportsman const& lhs, Sportsman const& rhs)
{
	return lhs.name < rhs.name;
}