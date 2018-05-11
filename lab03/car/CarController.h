#pragma once
#include "Car.h"
#include <functional>
#include <map>

class CCarController
{
public:
	CCarController(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	void EngineOn(std::istream& args);
	void EngineOff(std::istream& args);
	void Info(std::istream& args) const;
	void SetGear(std::istream& args);
	void SetSpeed(std::istream& args);

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream& args)>>;

	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	CCar& m_car;
};
