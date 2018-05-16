#include "stdafx.h"
#include "../FourthDegreeEquation/Math.cpp"
#include "../FourthDegreeEquation/VariantUtils.h"

SCENARIO("Test Solve2")
{
	GIVEN("Quadratic equation")
	{
		WHEN("a = 0")
		{
			auto result = Solve2(0.0, 1.7, 2.0);

			THEN("This not a quadratic equation")
			{
				REQUIRE(VeriantUtills::get_if<NotAQuadraticEquation>(&result));
			}
		}

		WHEN("discriminant < 0")
		{
			auto result = Solve2(10.0, 2.0, 100.0);

			THEN("No reals roots")
			{
				REQUIRE(VeriantUtills::get_if<std::monostate>(&result));
			}
		}

		WHEN("discriminant == 0")
		{
			auto result = Solve2(2.0, 4.0, 2.0);

			THEN("One real root")
			{
				if (auto singleRoot = VeriantUtills::get_if<double>(&result))
				{
					REQUIRE(IsEqual(*singleRoot, -1.0));
				}
				else
				{
					REQUIRE(false);
				}
			}
		}

		WHEN("discriminant > 0.0")
		{
			auto result = Solve2(2.0, 15.0, 2.0);

			THEN("Two real roots")
			{
				if (auto twoRoots = VeriantUtills::get_if<std::pair<double, double>>(&result))
				{
					REQUIRE(IsEqual(twoRoots->first, -7.3642080737002402));
					REQUIRE(IsEqual(twoRoots->second, -0.13579192629975978));
				}
				else
				{
					REQUIRE(false);
				}
			}
		}
	}
}

SCENARIO("Solve3 test")
{
	GIVEN("Cubic equation")
	{
		WHEN("first coefficient is equal a 0.0")
		{
			THEN("throw an expcetion 'a in  ax^3 + bx^2 + cx + e = 0 can't be empty'")
			{
				try
				{
					auto result = Solve3(0.0, 15.0, 2.0, 2.0);
				}
				catch (std::exception const& err)
				{
					std::stringstream strm;
					strm << err.what();

					REQUIRE(strm.str() == std::string("a in  ax^3 + bx^2 + cx + e = 0 can't be empty"));
				}
			}
		}

		WHEN("S > 0. S = Q * Q * Q - R * R;  R = (2 * a * a * a - 9 * a * b + 27 * c) / 54.0;  (a * a - 3 * b) / 9.0; in x^3 + ax^2 + bx + c = 0")
		{
			THEN("three real root")
			{
				try
				{
					auto result = Solve3(-3.0, 45.0, 4.0, -5.0);

					REQUIRE(result.numRoots == 3);
					CHECK(IsEqual(result.roots[0], -0.37544050338827528));
					CHECK(IsEqual(result.roots[1], 15.081083010225125));
					CHECK(IsEqual(result.roots[2], 0.29435749316314741));
				}
				catch (...)
				{
					REQUIRE(false);
				}
			}
		}

		WHEN("S == 0; S = Q * Q * Q - R * R;  R = (2 * a * a * a - 9 * a * b + 27 * c) / 54.0;  (a * a - 3 * b) / 9.0; in x^3 + ax^2 + bx + c = 0")
		{
			THEN("1 real root")
			{
				try
				{
					auto result = Solve3(1.0, -9.0, 15.0, 25.0);

					REQUIRE(result.numRoots == 3);
					CHECK(IsEqual(result.roots[0], -1.0));
					CHECK(IsEqual(result.roots[1], 5.0));
					CHECK(!IsEqual(result.roots[2], result.roots[2]));
				}
				catch (...)
				{
					REQUIRE(false);
				}
			}
		}


		WHEN("S < 0; S = Q * Q * Q - R * R;  R = (2 * a * a * a - 9 * a * b + 27 * c) / 54.0;  (a * a - 3 * b) / 9.0; in x^3 + ax^2 + bx + c = 0")
		{
			AND_WHEN("Q > 0")
			{
				THEN("1 real root")
				{
					try
					{
						auto result = Solve3(1.0, -6, 5.0, -12.0);

						REQUIRE(result.numRoots == 3);
						CHECK(IsEqual(result.roots[0], 5.4873384444522291));
						CHECK(!IsEqual(result.roots[1], result.roots[1]));
						CHECK(!IsEqual(result.roots[2], result.roots[2]));
					}
					catch (...)
					{
						REQUIRE(false);
					}
				}
			}
			
			AND_WHEN("Q < 0")
			{
				THEN("1 real root")
				{
					try
					{
						auto result = Solve3(1.0, 3.0, 675.0, -12.0);

						REQUIRE(result.numRoots == 3);
						CHECK(IsEqual(result.roots[0], 0.017776365015147899));
						CHECK(!IsEqual(result.roots[1], result.roots[1]));
						CHECK(!IsEqual(result.roots[2], result.roots[2]));
					}
					catch (...)
					{
						REQUIRE(false);
					}
				}
			}
			
			AND_WHEN("Q == 0")
			{
				THEN("1 real root")
				{
					try
					{
						auto result = Solve3(1.0, 3.0, 3.0, 12.0);

						REQUIRE(result.numRoots == 3);
						CHECK(IsEqual(result.roots[0], -2.0));
						CHECK(!IsEqual(result.roots[1], result.roots[1]));
						CHECK(!IsEqual(result.roots[2], result.roots[2]));
					}
					catch (...)
					{
						REQUIRE(false);
					}
				}
			}
		}
	}
}

SCENARIO("Solve4")
{
	GIVEN("4 degree equation")
	{
		WHEN("first coefficient is equal a 0.0")
		{
			THEN("throw an expcetion a in 'ax^4 + bx^3 + cx^2 + dx + e = 0'")
			{
				try
				{
					auto result = Solve4(0.0, 15.0, 2.0, 2.0, 0.0);
				}
				catch (std::exception const& err)
				{
					std::stringstream strm;
					strm << err.what();

					REQUIRE(strm.str() == std::string("A zero coefficinet value is not allowed for x4"));
				}
			}
		}

		WHEN("first coefficient is not equal a 0.0")
		{
			THEN("number roots is a fourth")
			{
				try
				{
					auto result = Solve4(1, 4, -4, -20, -5);

					REQUIRE(IsEqual(result.roots[0], -3.7320508075688781));
					REQUIRE(IsEqual(result.roots[1], 2.2360679774997902));
					REQUIRE(IsEqual(result.roots[2], -2.2360679774997889));
					REQUIRE(IsEqual(result.roots[3], -0.26794919243112347));
				}
				catch (...)
				{
					REQUIRE(false);
				}
			}
		}
		
		WHEN("first coefficient is not equal a 0.0")
		{
			THEN("number roots is a two")
			{
				try
				{
					auto result = Solve4(1, 45, -1, -1, 5);

					REQUIRE(IsEqual(result.roots[2], -45.021663386846171));
					REQUIRE(IsEqual(result.roots[3], -0.49041761698392605));
				}
				catch (...)
				{
					REQUIRE(false);
				}
			}
		}
	}
}