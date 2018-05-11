#include "stdafx.h"
#include "Car.h"

bool CCar::IsTurnedOnEngine() const
{
	return m_turnedOn;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

Gear CCar::GetGear() const
{
	return m_gear;
}

std::string CCar::GetDirectionMovement() const
{
	if (m_speed == 0)
	{
		return "not moving";
	}
	else if (m_speed < 0)
	{
		return "backword moving";
	}
	else
	{
		return "forward moving";
	}
}

bool CCar::TurnOnEngine()
{
	if (m_turnedOn)
	{
		return false;
	}

	m_gear = Gear::Neutral;
	m_turnedOn = true;

	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_turnedOn && m_gear == Gear::Neutral && m_speed == 0)
	{
		m_turnedOn = false;

		return true;
	}

	return false;
}

constexpr int MIN_SPEED = -20;
constexpr int MAX_SPEED = 150;

static const std::map<Gear, SpeedRange> GEAR_SPEED_RANGE = {
	{ Gear::Reverse, { -20, 0 } },
	{ Gear::Neutral, { MIN_SPEED, MAX_SPEED } },
	{ Gear::First, { 0, 30 } },
	{ Gear::Second, { 20, 50 } },
	{ Gear::Third, { 30, 60 } },
	{ Gear::Fourth, { 40, 90 } },
	{ Gear::Fifth, { 50, 150 } }
};

bool CCar::IsPermissibleGearForSpeed(Gear gear, int speed) const
{
	SpeedRange rangeOfSpeed = GEAR_SPEED_RANGE.at(gear);

	return speed >= rangeOfSpeed.min && speed <= rangeOfSpeed.max;
}

bool CCar::TransmissionCanBeSwitched(Gear gear) const
{
	return (m_speed == 0 && (gear == Gear::Reverse || (gear == Gear::First && m_gear == Gear::Reverse)))
		|| (IsPermissibleGearForSpeed(gear, m_speed) && gear != Gear::Reverse);
}

bool CCar::SetGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		return false;
	}

	Gear gearType = static_cast<Gear>(gear);

	if ((m_turnedOn && TransmissionCanBeSwitched(gearType))
		|| (!m_turnedOn && gearType == Gear::Neutral))
	{
		m_gear = gearType;

		return true;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{	
	if (m_turnedOn)
	{
		if (m_gear == Gear::Reverse)
		{
			speed = -speed;
		}
		if ((IsPermissibleGearForSpeed(m_gear, speed) && m_gear != Gear::Neutral)
			|| (m_gear == Gear::Neutral && abs(speed) <= abs(m_speed)))
		{
			m_speed = speed;

			return true;
		}
	}

	return false;
}
