#pragma once

struct Sportsman
{
	Sportsman(std::string const& lfm = "", int growth = 190, int weight = 100);
	bool operator<(Sportsman const& other);
	bool operator==(const Sportsman& other);

	std::string lfm;
	int growth;
	int weight;
};