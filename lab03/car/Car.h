#pragma once

enum class Gear
{
	Reverse = -1,
	Neutral = 0,
	First = 1,
	Second = 2,
	Third = 3,
	Fourth = 4,
	Fifth = 5,
};

struct SpeedRange
{
	int min = 0;
	int max = 0;
};

class CCar
{
public:
	bool IsTurnedOnEngine() const;
	int GetSpeed() const;
	std::string GetDirectionMovement() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int gear);

private:
	bool IsPermissibleGearForSpeed(Gear gear, int speed) const;
	bool TransmissionCanBeSwitched(Gear gear) const;

private:
	bool m_turnedOn = false;
	int m_speed = 0; 
	Gear m_gear = Gear::Neutral;
};
