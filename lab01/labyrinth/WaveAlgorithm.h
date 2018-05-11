#pragma once

constexpr size_t MAP_HEIGHT = 100;
constexpr size_t MAP_WIDTH = 100;
constexpr size_t TOTAL_MAP_HEIGHT = MAP_HEIGHT + 2;
constexpr size_t TOTAL_MAP_WIDTH = MAP_WIDTH + 2;

using Map = std::array<std::array<int, TOTAL_MAP_WIDTH>, TOTAL_MAP_HEIGHT>;

enum class ErrorType
{
	None,
	UnresolvedSymbol,
	InvalidNumberOfStartingPosition,
	InvalidNumberOfEndingPosition
};

struct Coordinate
{
	int x = 0;
	int y = 0;
};

struct Labyrinth
{
	Coordinate start;
	Coordinate end;
	Map map;
};

std::string GetErrorMessage(const ErrorType &errorType);
ErrorType ReadLabyrinth(std::istream &input, Labyrinth &labyrinth);
void PrintLabyrinth(std::ostream &output, const Labyrinth &labyrinth);
void WaveAlgorithm(Labyrinth &labyrinth);