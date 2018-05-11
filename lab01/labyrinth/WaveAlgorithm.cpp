#include "stdafx.h"
#include "WaveAlgorithm.h"
#include <functional>


enum class CharValueOfCell : char
{
	START = 'A',
	END = 'B',
	WALL = '#',
	BLANK = ' ',
	PATH = '.',
};

enum class NumericValueOfCell : int
{
	START = 0,
	END = -1,
	WALL = -2,
	BLANK = -3,
	PATH = -4,
};

static const unsigned VALID_NUMBER_STARTING_CELL = 1;
static const unsigned VALID_NUMBER_ENDING_CELL = 1;

struct LabyrinthStats
{
	int numberBeginPoints = 0;
	int numberEndPoints = 0;
	ErrorType errorType = ErrorType::None;
};

static const std::vector<std::pair<CharValueOfCell, NumericValueOfCell>> CHAR_VALUE_OF_CELL_TO_NUMERIC = {
	std::make_pair(CharValueOfCell::START, NumericValueOfCell::START),
	std::make_pair(CharValueOfCell::END, NumericValueOfCell::END),
	std::make_pair(CharValueOfCell::WALL, NumericValueOfCell::WALL),
	std::make_pair(CharValueOfCell::BLANK, NumericValueOfCell::BLANK),
	std::make_pair(CharValueOfCell::PATH, NumericValueOfCell::PATH)
};
//
//static const std::map<CharValueOfCell, NumericValueOfCell> CHAR_TO_NUMBER = {
//	{ CharValueOfCell::START, NumericValueOfCell::START},
//	{ CharValueOfCell::END, NumericValueOfCell::END },
//	{ CharValueOfCell::WALL, NumericValueOfCell::WALL },
//	{ CharValueOfCell::BLANK, NumericValueOfCell::BLANK },
//	{ CharValueOfCell::PATH, NumericValueOfCell::PATH }
//};

static const std::vector<std::pair<ErrorType, std::string>> MESSAGE_TYPE_ERROR = {
	std::make_pair(ErrorType::InvalidNumberOfStartingPosition, "Invalid number of occuerance of the starting position labirinth."),
	std::make_pair(ErrorType::InvalidNumberOfEndingPosition, "Invalid number of occuerance of the ending position labirinth."),
	std::make_pair(ErrorType::UnresolvedSymbol, "Unresolved symbol in the map of the labirinth.")
};

static const size_t NUMBER_DIRECTIONS = 4;
static const Coordinate DIRECTIONS[NUMBER_DIRECTIONS] = {
	{ 1, 0 },
	{ 0, 1 },
	{ -1, 0 },
	{ 0, -1 }
};

namespace
{
	void SetCell(Labyrinth &labyrinth, size_t x, size_t y, const NumericValueOfCell &value)
	{
		labyrinth.map.at(y).at(x) = static_cast<int>(value);
	}

	NumericValueOfCell GetCell(const Labyrinth &labyrinth, size_t x, size_t y)
	{
		return static_cast<NumericValueOfCell>(labyrinth.map.at(y).at(x));
	}

	void SetCell(Labyrinth &labyrinth, const Coordinate &coordinate, const NumericValueOfCell &value)
	{
		labyrinth.map.at(coordinate.y).at(coordinate.x) = static_cast<int>(value);
	}

	NumericValueOfCell GetCell(const Labyrinth &labyrinth, const Coordinate &coordinate)
	{
		return static_cast<NumericValueOfCell>(labyrinth.map.at(coordinate.y).at(coordinate.x));
	}

	void InitLabyrinth(Labyrinth &labyrinth)
	{
		for (auto &row : labyrinth.map)
		{
			row.fill(static_cast<int>(NumericValueOfCell::BLANK));
		}
	}

	template <typename TypeFirst, typename TypeSecond>
	bool FoundByKey(const std::vector<std::pair<TypeFirst, TypeSecond>> &vector, const TypeFirst &key, TypeSecond &value)
	{
		auto isEqual = [&key](const std::pair<TypeFirst, TypeSecond> &element)
		{
			return element.first == key;
		};

		auto it = std::find_if(vector.begin(), vector.end(), isEqual);
		
		if (it != vector.end())
		{
			value = it->second;

			return true;
		}

		return false;
	}

	bool FoundByValue(const NumericValueOfCell &foundNumber, CharValueOfCell &ch)
	{
		auto isEqual = [&foundNumber](const std::pair<CharValueOfCell, NumericValueOfCell> &element)
		{
			return element.second == foundNumber;
		};

		auto it = std::find_if(CHAR_VALUE_OF_CELL_TO_NUMERIC.begin(), CHAR_VALUE_OF_CELL_TO_NUMERIC.end(), isEqual);

		if (it != std::end(CHAR_VALUE_OF_CELL_TO_NUMERIC))
		{
			ch = it->first;

			return true;
		}

		return false;
	}

	char GetCharacterValueOfCell(const Labyrinth &labyrinth, size_t x, size_t y)
	{
		NumericValueOfCell cellValue = GetCell(labyrinth, x, y);
		CharValueOfCell ch;
		char result = ' ';

		if (static_cast<int>(cellValue) > 0)
		{
			result = static_cast<char>(CharValueOfCell::BLANK);
		}
		else if (FoundByValue(cellValue, ch))
		{
			result = static_cast<char>(ch);
		}

		return result;
	}

	bool GetNumericalRepresentionOfChar(char ch, NumericValueOfCell &numericValueOfCell)
	{
		CharValueOfCell charValueOfCell = static_cast<CharValueOfCell>(ch);
	
		return FoundByKey(CHAR_VALUE_OF_CELL_TO_NUMERIC, charValueOfCell, numericValueOfCell);
	}

	void ReadRow(const std::string &str, Labyrinth &labyrinth, LabyrinthStats &labyrinthStats, int y)
	{
		for (auto x = 0; x < str.size() && x < MAP_WIDTH; ++x)
		{
			NumericValueOfCell cellNumberValue;

			if (!GetNumericalRepresentionOfChar(str[x], cellNumberValue))
			{
				labyrinthStats.errorType = ErrorType::UnresolvedSymbol;
			}
			else if (cellNumberValue == NumericValueOfCell::START)
			{
				labyrinth.start = { x + 1, y + 1 };
				labyrinthStats.numberBeginPoints++;
			}
			else if (cellNumberValue == NumericValueOfCell::END)
			{
				labyrinth.end = { x + 1, y + 1 };
				labyrinthStats.numberEndPoints++;
			}

			SetCell(labyrinth, x + 1, y + 1, cellNumberValue);
		}
	}

	bool IsBorderCell(const Coordinate &coordinate)
	{
		return (coordinate.x == 0) || (coordinate.x == (TOTAL_MAP_WIDTH - 1))
			|| (coordinate.y == 0) || (coordinate.y == (TOTAL_MAP_HEIGHT - 1));
	}

	bool IsCellBlank(const Map &map, const Coordinate &coordinate)
	{
		return map[coordinate.y][coordinate.x] == static_cast<int>(NumericValueOfCell::BLANK);
	}

	bool IsNotVisitedCell(const Map &map, const Coordinate coordinate)
	{
		return (!IsBorderCell(coordinate) && IsCellBlank(map, coordinate));
	}

	bool WavePropagationInNeighboringCells(Map &map, const Coordinate &current,
		std::queue<Coordinate> &queue)
	{
		bool foundPath = false;

		for (const auto &direction : DIRECTIONS)
		{
			Coordinate neighboringCellCoordinate = { current.x + direction.x,
				current.y + direction.y };

			if (map[neighboringCellCoordinate.y][neighboringCellCoordinate.x] == static_cast<int>(NumericValueOfCell::END))
			{
				map[neighboringCellCoordinate.y][neighboringCellCoordinate.x] = map[current.y][current.x] + 1;
				foundPath = true;
			}
			else if (IsNotVisitedCell(map, neighboringCellCoordinate))
			{
				queue.push(neighboringCellCoordinate);
				map[neighboringCellCoordinate.y][neighboringCellCoordinate.x] = map[current.y][current.x] + 1;
			}
		}

		return foundPath;
	}

	bool WavePropagation(Labyrinth &labyrinth)
	{
		bool foundPath = false;

		std::queue<Coordinate> queue;
		queue.push(labyrinth.start);

		while (!queue.empty() && !foundPath)
		{
			Coordinate currentCoordinate = queue.front();
			queue.pop();

			foundPath = WavePropagationInNeighboringCells(labyrinth.map, currentCoordinate, queue);
		}

		return foundPath;
	}

	bool IsNextCoordinate(const Labyrinth &labyrinth, const Coordinate &current, const  Coordinate &nextPathCellCoordinate)
	{
		int nextPathCellValue = static_cast<int>(GetCell(labyrinth, nextPathCellCoordinate));
		int currentCellValue = static_cast<int>(GetCell(labyrinth, current));

		return (nextPathCellValue == currentCellValue - 1 && !IsBorderCell(nextPathCellCoordinate));
	}

	Coordinate FindNextPathCell(Labyrinth &labyrinth, const Coordinate &current)
	{
		Coordinate nextPathCellCoordinate;

		for (const auto &direction : DIRECTIONS)
		{
			nextPathCellCoordinate = { current.x + direction.x, current.y + direction.y };

			if (IsNextCoordinate(labyrinth, current, nextPathCellCoordinate))
			{
				SetCell(labyrinth, current, NumericValueOfCell::PATH);
				break;
			}
		}

		return nextPathCellCoordinate;
	}

	void PathRecovery(Labyrinth &labyrinth)
	{
		Coordinate currentCoordinate = labyrinth.end;

		while (GetCell(labyrinth, currentCoordinate) != NumericValueOfCell::START)
		{
			currentCoordinate = FindNextPathCell(labyrinth, currentCoordinate);
		}

		SetCell(labyrinth, labyrinth.end, NumericValueOfCell::END);
	}
}

std::string GetErrorMessage(const ErrorType &errorType)
{
	std::string result;

	return (FoundByKey(MESSAGE_TYPE_ERROR, errorType, result)) ? result : "";
}

ErrorType ReadLabyrinth(std::istream &input, Labyrinth &labyrinth)
{
	InitLabyrinth(labyrinth);

	std::string row;
	LabyrinthStats labyrinthStats;

	for (auto y = 0; std::getline(input, row) && y < MAP_HEIGHT; ++y)
	{
		ReadRow(row, labyrinth, labyrinthStats, y);

		if (labyrinthStats.errorType == ErrorType::UnresolvedSymbol)
		{
			return ErrorType::UnresolvedSymbol;
		}
	}

	if (labyrinthStats.numberBeginPoints != VALID_NUMBER_STARTING_CELL)
	{
		return ErrorType::InvalidNumberOfStartingPosition;
	}
	if (labyrinthStats.numberEndPoints != VALID_NUMBER_ENDING_CELL)
	{
		return ErrorType::InvalidNumberOfEndingPosition;
	}

	return ErrorType::None;
}

void PrintLabyrinth(std::ostream &output, const Labyrinth &labyrinth)
{
	for (auto y = 1; y < MAP_HEIGHT + 1; ++y)
	{
		for (auto x = 1; x < MAP_WIDTH; ++x)
		{
			output << GetCharacterValueOfCell(labyrinth, x, y);
		}

		output << "\n";
	}
}

void WaveAlgorithm(Labyrinth &labyrinth)
{
	if (WavePropagation(labyrinth))
	{
		PathRecovery(labyrinth);
	}
}
