#include "stdafx.h"
#include "../calculator/CalculateOperation.cpp"
#include "../calculator/Calculator.cpp"


void TestLetVariable(CCalculator& calculator, const std::string& variableId, const std::string& value, const std::string& expectedOutput, bool isSuccess)
{
	REQUIRE(calculator.LetVariable(variableId, value) == isSuccess);

	std::string variablesValue = calculator.GetValuesOfVariables();

	REQUIRE(variablesValue == expectedOutput);
}

void TestLetVariable(CCalculator& calculator, const std::string& variableId, double value, const std::string& expectedOutput, bool isSuccess)
{
	REQUIRE(calculator.LetVariable(variableId, value) == isSuccess);

	std::string variablesValue = calculator.GetValuesOfVariables();

	REQUIRE(variablesValue == expectedOutput);
}

struct FunctionData
{
	FunctionData()
	{
	}

	FunctionData(std::string const& firstId, std::string const& operation, std::string const& secondId)
		: firstId(firstId)
		, operation(operation)
		, secondId(secondId)
	{
	}

	std::string firstId;
	std::string operation;
	std::string secondId;
};

void TestInitFunction(CCalculator& calculator, const std::string& funcId, FunctionData const& funcValue, double expectedValue, bool isSuccess)
{
	REQUIRE(calculator.InitFunction(funcId, funcValue.firstId, funcValue.operation, funcValue.secondId) == isSuccess);

	if (isSuccess)
	{
		double value = 0.0;

		REQUIRE(calculator.GetValueByIdentitifer(funcId, value) == isSuccess);

		if (value == value)
		{
			REQUIRE(value == expectedValue);
		}
	}
}

void TestInitFunction(CCalculator& calculator, const std::string& funcId, std::string const& valueId, double expectedValue, bool isSuccess)
{
	REQUIRE(calculator.InitFunction(funcId, valueId) == isSuccess);

	if (isSuccess)
	{
		double value = 0.0;

		REQUIRE(calculator.GetValueByIdentitifer(funcId, value) == isSuccess);

		if (value == value)
		{
			REQUIRE(value == expectedValue);
		}
	}
}

SCENARIO("Test calculator")
{
	CCalculator calculator;

	GIVEN("calculator")
	{
		WHEN("Initially")
		{
			THEN("allow to declare variable with valid identifier")
			{
				REQUIRE(calculator.DeclareVariable("x"));
				REQUIRE(calculator.DeclareVariable("x1"));
				REQUIRE(calculator.DeclareVariable("x_"));
				REQUIRE(calculator.DeclareVariable("_x"));
				REQUIRE(calculator.DeclareVariable("m_variables"));
				REQUIRE(calculator.DeclareVariable("m_Wwerq123"));
				REQUIRE(calculator.DeclareVariable("_x_"));

				std::string variablesValue = calculator.GetValuesOfVariables();

				REQUIRE(variablesValue == "_x:nan\n_x_:nan\nm_Wwerq123:nan\nm_variables:nan\nx:nan\nx1:nan\nx_:nan\n");
			}

			THEN("does not allow to declare exist variable")
			{
				REQUIRE(calculator.DeclareVariable("x"));
				REQUIRE(!calculator.DeclareVariable("x"));

				std::string variablesValue = calculator.GetValuesOfVariables();

				REQUIRE(variablesValue == std::string("x:nan\n"));
			}

			AND_WHEN("Let exist variable")
			{
				calculator.DeclareVariable("x");
				calculator.DeclareVariable("y");

				THEN("does allow to let exist function identifer")
				{
					TestLetVariable(calculator, "q", 2, "q:2.00\nx:nan\ny:nan\n", true);
					TestInitFunction(calculator, "e", FunctionData("q", "*", "q"), 4, true);
					TestLetVariable(calculator, "e", 123.01, "q:2.00\nx:nan\ny:nan\n", false);
				}

				THEN("allow to init with number value")
				{
					TestLetVariable(calculator, "x", 123.01, "x:123.01\ny:nan\n", true);
				}

				THEN("allow to init with value of exist variable")
				{
					TestLetVariable(calculator, "y", "x", "x:nan\ny:nan\n", true);
				}

				THEN("allow to init unexist identifier with number")
				{
					TestLetVariable(calculator, "z", 23.12, "x:nan\ny:nan\nz:23.12\n", true);
				}
			}

			AND_WHEN("Init not exist variable")
			{
				THEN("allow to init with number value")
				{
					TestLetVariable(calculator, "x", 123.01, "x:123.01\n", true);
				}

				THEN("allow to init with value of exist variable")
				{
					TestLetVariable(calculator, "x", 123.01, "x:123.01\n", true);
					TestLetVariable(calculator, "y", "x", "x:123.01\ny:123.01\n", true);
				}

				THEN("allow to init unexist identifier with number")
				{
					TestLetVariable(calculator, "z", 23.12, "z:23.12\n", true);
				}

				THEN("allow to init with exist function value")
				{
					TestLetVariable(calculator, "x", 123.01, "x:123.01\n", true);
					TestInitFunction(calculator, "X", "x", 123.01, true);

					TestLetVariable(calculator, "y", "X", "x:123.01\ny:123.01\n", true);

					double value = 0.0;

					REQUIRE(calculator.GetValueByIdentitifer("y", value));
					REQUIRE(value == 123.01);
				}
			}

			AND_WHEN("Init function")
			{
				THEN("not allow to init value str of not exist variable")
				{
					TestInitFunction(calculator, "x", "y", std::numeric_limits<double>::quiet_NaN(), false);
				}

				THEN("not allow to init value str of not exist identifier")
				{
					TestInitFunction(calculator, "x", "y", std::numeric_limits<double>::quiet_NaN(), false);
				}

				THEN("allow to init a variable with a value of nan")
				{
					REQUIRE(calculator.DeclareVariable("a"));
					TestInitFunction(calculator, "d", "a", std::numeric_limits<double>::quiet_NaN(), true);
				}

				THEN("not allow to init a not exist identifier")
				{
					REQUIRE(calculator.DeclareVariable("a"));

					TestInitFunction(calculator, "a", FunctionData("a", "+", "Exception"), std::numeric_limits<double>::quiet_NaN(), false);
				}

				THEN("allow to init a sum of exist variables")
				{
					TestLetVariable(calculator, "q", 2, "q:2.00\n", true);
					TestInitFunction(calculator, "qwerty", FunctionData("q", "+", "q"), 4.00, true);
				}

				THEN("allow to init a difference of exist variables")
				{
					TestLetVariable(calculator, "q", 2, "q:2.00\n", true);
					TestInitFunction(calculator, "w", FunctionData("q", "-", "q"), 0.00, true);
				}

				THEN("allow to init a multiplication of exist variables")
				{
					TestLetVariable(calculator, "q", 2, "q:2.00\n", true);
					TestInitFunction(calculator, "e", FunctionData("q", "*", "q"), 4.00, true);
				}

				THEN("throws an exception when dividing by zero")
				{
					try
					{
						TestLetVariable(calculator, "q", 0, "q:0.00\n", true);
						TestLetVariable(calculator, "w", 2, "q:0.00\nw:2.00\n", true);
						TestInitFunction(calculator, "f", FunctionData("q", "/", "q"), std::numeric_limits<double>::quiet_NaN(), true);
					}
					catch (std::logic_error const& err)
					{
						std::stringstream strm;
						strm << err.what();
						REQUIRE(strm.str() == "devision by zero");
					}
					catch (...)
					{
						REQUIRE(true);
					}
				}

				THEN("allow to init a divisions of exist variables")
				{
					TestLetVariable(calculator, "q", 2, "q:2.00\n", true);
					TestInitFunction(calculator, "d", FunctionData("q", "/", "q"), 1.00, true);
				}

				THEN("allow calculate fibonacci number")
				{
					REQUIRE(calculator.LetVariable("v0", 0));
					REQUIRE(calculator.LetVariable("v1", 1));
					TestInitFunction(calculator, "fib0", "v0", 0.00, true);
					TestInitFunction(calculator, "fib1", "v1", 1.00, true);
					TestInitFunction(calculator, "fib2", FunctionData("fib1", "+", "fib0"), 1.00, true);
					TestInitFunction(calculator, "fib3", FunctionData("fib2", "+", "fib1"), 2.00, true);
					TestInitFunction(calculator, "fib4", FunctionData("fib3", "+", "fib2"), 3.00, true);
				}
			}
		}
	}
}

TEST_CASE("get value")
{
	CCalculator calculator;

	SECTION("GetValueByIdentitifer not exist identifier failed")
	{
		double value = 0.0;

		REQUIRE_FALSE(calculator.GetValueByIdentitifer("q", value));
	}

	SECTION("GetValuesOfFunctions exist function")
	{
		REQUIRE(calculator.LetVariable("v0", 0));
		TestInitFunction(calculator, "fib0", "v0", 0.00, true);
	
		std::string valueOfFunctions = calculator.GetValuesOfFunctions();

		REQUIRE(valueOfFunctions == "fib0:0.00\n");
	}
}