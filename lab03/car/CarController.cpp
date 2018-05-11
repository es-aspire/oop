#include "stdafx.h"
#include "CarController.h"

namespace
{

bool StringToInt(const std::string& str, int& number)
{
	try
	{
		number = stoi(str);
		return true;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
		return false;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << "\n";
		return false;
	}
}

} // namespace

CCarController::CCarController(CCar& car, std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_car(car)
	, m_actionMap({
		  { "Info", std::bind(&CCarController::Info, this, std::placeholders::_1) },
		  { "EngineOn", std::bind(&CCarController::EngineOn, this, std::placeholders::_1) },
		  { "EngineOff", std::bind(&CCarController::EngineOff, this, std::placeholders::_1) },
		  { "SetSpeed", std::bind(&CCarController::SetSpeed, this, std::placeholders::_1) },
		  { "SetGear", std::bind(&CCarController::SetGear, this, std::placeholders::_1) },
	  })
{
}

bool CCarController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CCarController::SetGear(std::istream& args)
{
	std::string str;
	args >> str;

	if (str.empty())
	{
		m_output << "gear can not be empty\n";
	}
	else
	{
		int gear = 0;
		if (!StringToInt(str, gear))
		{
			m_output << "gear should be number\n";
		}
		else if (m_car.SetGear(gear))
		{
			m_output << "set gear success\n"; 
		}
		else
		{
			m_output << "set gear failed\n";
		}
	}
}

void CCarController::SetSpeed(std::istream& args)
{
	std::string str;
	args >> str;

	if (str.empty())
	{
		m_output << "speed can not be empty\n";
	}
	else
	{
		int speed = 0;

		if (!StringToInt(str, speed))
		{
			m_output << "speed should be number\n";
		}
		else if (m_car.SetSpeed(speed))
		{
			m_output << "set speed success\n";
		}
		else
		{
			m_output << "set speed failed\n";
		}
	}
	
}

void CCarController::EngineOn(std::istream& args)
{
	m_output << "Car engine ";

	if (m_car.TurnOnEngine())
	{
		m_output << "is turned on\n";
	}
	else
	{
		m_output << "cann't be turned on\n";
	}
}

void CCarController::EngineOff(std::istream& args)
{
	m_output << "Car engine ";

	if (m_car.TurnOffEngine())
	{
		m_output << "is turned off\n";
	}
	else
	{
		m_output << "cann't be turned off\n";
	}
}

static const std::map<Gear, std::string> GEAR_TO_STRING = {
	{ Gear::Reverse, "reverse" },
	{ Gear::Neutral, "neutral" },
	{ Gear::First, "first" },
	{ Gear::Second, "second" },
	{ Gear::Third, "third" },
	{ Gear::Fourth, "fourth" },
	{ Gear::Fifth, "fifth" },
};

void CCarController::Info(std::istream& args) const
{
	std::string directionMovementStr = m_car.GetDirectionMovement();

	Gear gear = m_car.GetGear();
	std::string gearStr = GEAR_TO_STRING.at(gear);

	int speed = m_car.GetSpeed();

	m_output << "Car info: \n"
			 << " - the condition of the car engine: " << ((m_car.IsTurnedOnEngine()) ? "on" : "off") << "\n"
			 << " - speed: " << speed << "\n"
			 << " - direction of movement: " << directionMovementStr << "\n"
			 << " - gear: " << gearStr << "\n";
}
