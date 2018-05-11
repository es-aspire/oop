#include "stdafx.h"
#include "../car/Car.cpp"

namespace
{

void CheckSetGear(CCar& car, int selectedGear, const Gear& checkGear, bool state)
{
	CHECK(car.SetGear(selectedGear) == state);
	REQUIRE(car.GetGear() == checkGear);
}

using GearTestData = std::tuple<int, Gear, bool>;

void SetGearTests(CCar& car, const std::vector<GearTestData>& checkData)
{
	for (const auto& item : checkData)
	{
		CheckSetGear(car, std::get<0>(item), std::get<1>(item), std::get<2>(item));
	}
}

void CheckSetSpeed(CCar& car, int selectedspeed, int checkSpeed, bool state)
{
	CHECK(car.SetSpeed(selectedspeed) == state);
	REQUIRE(car.GetSpeed() == checkSpeed);
}

using SpeedTestData = std::tuple<int, int, bool>;

void SetSpeedTests(CCar& car, const std::vector<SpeedTestData>& checkData)
{
	for (const auto& item : checkData)
	{
		CheckSetSpeed(car, std::get<0>(item), std::get<1>(item), std::get<2>(item));
	}
}
} // namespace

struct TestData
{
	using SpeedTestData = std::vector<SpeedTestData>;
	using GearTestData = std::vector<GearTestData>;

	int selectedGear = 0;
	Gear expectedGear;

	int selectedSpeed = 0;

	SpeedTestData permissibleSpeed;
	SpeedTestData impermissibleSpeed;

	GearTestData permissibleGear;
	GearTestData impermissibleGear;
};

class CGearTest
{
public:
	CGearTest() {}

	CGearTest(int selectedGear, int selectedSpeed);
	void Check(CCar& car);

private:
	void SwitchToSelectedGear(CCar& car, int selectedGear);
	void GenerateGearTestData(TestData& testData);
	void InitTestData(int selectedGear, int selectedSpeed);

private:
	TestData m_testData;
};

CGearTest::CGearTest(int selectedGear, int selectedSpeed)
{
	InitTestData(selectedGear, selectedSpeed);
}

void CGearTest::Check(CCar& car)
{
	SwitchToSelectedGear(car, m_testData.selectedGear);

	THEN("allow change speed in valid range")
	{
		SetSpeedTests(car, m_testData.permissibleSpeed);
	}

	AND_THEN("does not allow change speed in invalid range")
	{
		SetSpeedTests(car, m_testData.impermissibleSpeed);
	}

	AND_THEN("does not allow to switch to the transmission if the speed is within the impermissible range")
	{
		SetGearTests(car, m_testData.impermissibleGear);
	}

	AND_THEN("allow to switch to the transmission if the speed is within the permissible range")
	{
		SetGearTests(car, m_testData.permissibleGear);
	}

	AND_THEN("can't be turn off engine")
	{
		CHECK(!car.TurnOffEngine());
		CHECK(car.IsTurnedOnEngine());
	}
}

void CGearTest::SwitchToSelectedGear(CCar& car, int selectedGear)
{
	for (int i = 1; i <= selectedGear; ++i)
	{
		CheckSetGear(car, i, static_cast<Gear>(i), true);

		SpeedRange speedRange = GEAR_SPEED_RANGE.at(static_cast<Gear>(i));
		CheckSetSpeed(car, speedRange.min + 20, speedRange.min + 20, true);
	}
}

void CGearTest::GenerateGearTestData(TestData& testData)
{
	for (int i = -1; i < 6; ++i)
	{
		SpeedRange currentSpeedRange = GEAR_SPEED_RANGE.at(static_cast<Gear>(i));

		if (testData.selectedSpeed >= currentSpeedRange.min && testData.selectedSpeed <= currentSpeedRange.max)
		{
			testData.permissibleGear.emplace_back(i, static_cast<Gear>(i), true);
		}
		else
		{
			testData.impermissibleGear.emplace_back(i, static_cast<Gear>(testData.selectedGear), false);
		}
	}
}

void CGearTest::InitTestData(int selectedGear, int selectedSpeed)
{
	TestData testData;
	m_testData.selectedSpeed = selectedSpeed;
	m_testData.selectedGear = selectedGear;
	m_testData.expectedGear = static_cast<Gear>(selectedGear);

	SpeedRange speedRange = GEAR_SPEED_RANGE.at(m_testData.expectedGear);

	m_testData.impermissibleSpeed = {
		std::make_tuple(speedRange.min - 1, m_testData.selectedSpeed, false),
		std::make_tuple(speedRange.max + 1, m_testData.selectedSpeed, false)
	};

	m_testData.permissibleSpeed = {
		std::make_tuple(speedRange.min, speedRange.min, true),
		std::make_tuple(speedRange.min + 10, speedRange.min + 10, true),
		std::make_tuple(speedRange.min + 5, speedRange.min + 5, true),
		std::make_tuple(speedRange.max, speedRange.max, true),
	};

	GenerateGearTestData(m_testData);
}

TEST_CASE("Car")
{
	CCar car;

	GIVEN("Car")
	{
		WHEN("Initially")
		{
			THEN("turn is off, the speed is zero and not moving")
			{
				CHECK(!car.IsTurnedOnEngine());
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetDirectionMovement() == "not moving");
			}
		}

		WHEN("engine turn off")
		{
			REQUIRE(car.GetGear() == Gear::Neutral);
			REQUIRE(!car.IsTurnedOnEngine());

			THEN("cann't switch gears except for neutral")
			{
				std::vector<GearTestData> checkData = {
					std::make_tuple(-2, Gear::Neutral, false),
					std::make_tuple(-1, Gear::Neutral, false),
					std::make_tuple(0, Gear::Neutral, true),
					std::make_tuple(1, Gear::Neutral, false),
					std::make_tuple(2, Gear::Neutral, false),
					std::make_tuple(3, Gear::Neutral, false),
					std::make_tuple(4, Gear::Neutral, false),
					std::make_tuple(5, Gear::Neutral, false),
					std::make_tuple(6, Gear::Neutral, false)
				};

				SetGearTests(car, checkData);
			}

			AND_THEN("cann't change speed")
			{
				std::vector<SpeedTestData> checkData = {
					std::make_tuple(MIN_SPEED - 1, 0, false),
					std::make_tuple(MIN_SPEED, 0, false),
					std::make_tuple(-1, 0, false),
					std::make_tuple(0, 0, false),
					std::make_tuple(1, 0, false),
					std::make_tuple(16, 0, false),
					std::make_tuple(20, 0, false),
					std::make_tuple(50, 0, false),
					std::make_tuple(MAX_SPEED, 0, false),
					std::make_tuple(MAX_SPEED + 1, 0, false)
				};

				SetSpeedTests(car, checkData);
			}

			AND_THEN("can be turn on")
			{
				CHECK(car.TurnOnEngine());
				CHECK(car.IsTurnedOnEngine());
			}

			AND_THEN("cann't be turn off")
			{
				WHEN("speed is equal a zero and gear is not neutral")
				{
				}
			}

			WHEN("Only at zero speed on neutral transmission.")
			{
				CHECK(car.TurnOnEngine());
				CHECK(car.IsTurnedOnEngine());

				//AND_WHEN("")
			}

			AND_THEN("can be turn off")
			{

				CHECK(car.TurnOnEngine());
				CHECK(car.IsTurnedOnEngine());
				CHECK(car.TurnOffEngine());
				CHECK(!car.IsTurnedOnEngine());
			}
		}
	}
}

TEST_CASE("Car in the enabled state")
{
	GIVEN("Car")
	{
		CCar car;

		WHEN("engine turn on")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.IsTurnedOnEngine());

			THEN("speed is equal 0, gear is a netrual and not moving")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetGear() == Gear::Neutral);
				CHECK(car.GetDirectionMovement() == "not moving");
			}

			AND_THEN("allow switch to reverse gear")
			{
				CheckSetSpeed(car, 0, 0, true);
				CheckSetGear(car, -1, Gear::Reverse, true);
			}

			AND_THEN("allow switch to first gear")
			{
				CheckSetGear(car, 1, Gear::First, true);
			}

			WHEN("speed is equal a zero and gear is not a neutral gear")
			{
				CheckSetSpeed(car, 0, 0, true);
				CheckSetGear(car, 1, Gear::First, true);

				AND_THEN("does not allow to turn off engine")
				{
					CHECK(!car.TurnOffEngine());
					CHECK(car.IsTurnedOnEngine());
				}
			}

			AND_WHEN("speed is not equal a zero and gear is a neutral gear")
			{
				CheckSetGear(car, 1, Gear::First, true);
				CheckSetSpeed(car, 6, 6, true);
				CheckSetGear(car, 0, Gear::Neutral, true);

				AND_THEN("does not allow to turn off engine")
				{
					CHECK(!car.TurnOffEngine());
					CHECK(car.IsTurnedOnEngine());
				}
			}

			AND_WHEN("speed is not equal a zero and gear is not a neutral gear")
			{
				CheckSetGear(car, 1, Gear::First, true);
				CheckSetSpeed(car, 6, 6, true);

				AND_THEN("does not allow to turn off engine")
				{
					CHECK(!car.TurnOffEngine());
					CHECK(car.IsTurnedOnEngine());
				}
			}

			AND_WHEN("speed is equal a zero and gear is a neutral gear")
			{
				AND_THEN("allow to turn off engine")
				{
					CHECK(car.TurnOffEngine());
					CHECK(!car.IsTurnedOnEngine());
				}
			}
		}
	}
}

TEST_CASE("Selected gears tests")
{
	GIVEN("Select gears")
	{
		CCar car;
		CHECK(car.TurnOnEngine());
		CHECK(car.IsTurnedOnEngine());

		WHEN("selected gear is a neutral")
		{
			AND_WHEN("speed is equal 0")
			{
				CheckSetGear(car, 1, Gear::First, true);
				CheckSetSpeed(car, 0, 0, true);
				CheckSetGear(car, 0, Gear::Neutral, true);

				THEN("does not allow to switch to the transmission if the speed is within the impermissible range")
				{
					CheckSetGear(car, 2, Gear::Neutral, false);
					CheckSetGear(car, 3, Gear::Neutral, false);
					CheckSetGear(car, 4, Gear::Neutral, false);
					CheckSetGear(car, 5, Gear::Neutral, false);
					CheckSetGear(car, 6, Gear::Neutral, false);
				}

				AND_THEN("allow to switch to the transmission if the speed is within the permissible range")
				{
					CheckSetGear(car, -1, Gear::Reverse, true);
					CheckSetGear(car, 1, Gear::First, true);
				}

				AND_THEN("allow turn off engine")
				{
					REQUIRE(car.TurnOffEngine());
					REQUIRE(!car.IsTurnedOnEngine());
				}
			}

			AND_WHEN("speed is not equal 0")
			{
				CheckSetGear(car, 1, Gear::First, true);
				CheckSetSpeed(car, 20, 20, true);
				CheckSetGear(car, 0, Gear::Neutral, true);

				THEN("does not allow turn off engine")
				{
					CHECK(!car.TurnOffEngine());
					CHECK(car.IsTurnedOnEngine());
				}

				AND_THEN("does not allow selected reverse gear")
				{
					CheckSetGear(car, -1, Gear::Neutral, false);
				}

				AND_THEN("does not allow accelerate")
				{
					std::vector<SpeedTestData> checkData = {
						std::make_tuple(25, 20, false),
						std::make_tuple(20, 20, true),
						std::make_tuple(15, 15, true),
						std::make_tuple(10, 10, true),
						std::make_tuple(0, 0, true),
					};

					SetSpeedTests(car, checkData);
				}

				AND_THEN("allow to switch to a permissible gear")
				{
					CheckSetGear(car, 0, Gear::Neutral, true);
					CheckSetGear(car, 1, Gear::First, true);
					CheckSetGear(car, 2, Gear::Second, true);
				}

				AND_THEN("does not allow to switch to a impermissible gear")
				{
					CheckSetGear(car, -1, Gear::Neutral, false);
					CheckSetGear(car, 3, Gear::Neutral, false);
					CheckSetGear(car, 4, Gear::Neutral, false);
					CheckSetGear(car, 5, Gear::Neutral, false);
					CheckSetGear(car, 6, Gear::Neutral, false);
				}
			}
		}

		AND_WHEN("selected a reverse gear")
		{
			CheckSetGear(car, -1, Gear::Reverse, true);

			THEN("allow switch to first gear, when speed is equal 0")
			{
				CheckSetSpeed(car, 0, 0, true);
				CheckSetGear(car, 1, Gear::First, true);
			}

			CheckSetGear(car, -1, Gear::Reverse, true);

			AND_THEN("switching to neutral gear at non-zero speed in reverse, you can switch to the first gear only after stopping")
			{
				CheckSetSpeed(car, 6, 6, true);
				CheckSetGear(car, 0, Gear::Neutral, true);

				CheckSetGear(car, 1, Gear::Neutral, false);

				CheckSetSpeed(car, 0, 0, true);
				CheckSetGear(car, 1, Gear::First, true);
			}

			WHEN("speed is not equal a zero")
			{
				CheckSetSpeed(car, 6, 6, true);
				CheckSetGear(car, 0, Gear::Neutral, true);

				THEN("does not allow switch reverse gear")
				{
					CheckSetGear(car, -1, Gear::Neutral, false);
				}
			}

			AND_WHEN("speed is equal a zero")
			{
				CheckSetSpeed(car, 0, 0, true);
				CheckSetGear(car, 0, Gear::Neutral, true);

				THEN("allow switch reverse gear")
				{
					CheckSetGear(car, -1, Gear::Reverse, true);
				}
			}
		}

		AND_WHEN("switch a first gear")
		{
			CGearTest gearTest(1, 20);
			gearTest.Check(car);

			AND_WHEN("speed is not equal 0")
			{
				CheckSetSpeed(car, 3, 3, true);

				THEN("does not allow to switch reverse gear")
				{
					CHECK(!car.SetGear(-1));
					CHECK(car.GetGear() != Gear::Reverse);
				}
			}
		}

		AND_WHEN("switch a second gear")
		{
			CGearTest gearTest(2, 40);
			gearTest.Check(car);
		}

		AND_WHEN("switch a third gear")
		{
			CGearTest gearTest(3, 50);
			gearTest.Check(car);
		}

		AND_WHEN("switch a fourth gear")
		{
			CGearTest gearTest(4, 60);
			gearTest.Check(car);
		}

		AND_WHEN("switch a fifth gear")
		{
			CGearTest gearTest(5, 70);
			gearTest.Check(car);
		}
	}
}
