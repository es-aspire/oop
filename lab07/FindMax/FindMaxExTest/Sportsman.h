#pragma once

struct Sportsman
{
	Sportsman(std::string const& name = "", int growth = 190, int weight = 100);
	bool operator==(const Sportsman& other);

	std::string name;
	int growth;
	int weight;
};

bool operator<(Sportsman const& lhs, Sportsman const& rhs);