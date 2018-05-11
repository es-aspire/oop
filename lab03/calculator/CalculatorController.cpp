#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorController.h"

namespace
{
bool ParseString(const std::string& str, const std::string& patternString)
{
	if (str.empty())
	{
		return false;
	}

	std::regex pattern(patternString);
	std::smatch match;

	if (!std::regex_match(str, match, pattern))
	{
		return false;
	}

	return true;
}

bool IsDouble(const std::string& str)
{
	return ParseString(str, "^([-+]?)(0|([1-9][0-9]*))(\\.[0-9]+)?$");
}

static const std::string PATTERN_IDENTIFIER = "[A-Za-z_]([A-Za-z0-9_]+)?";
static const std::string PATTERN_OPERATION = "[+| -| *|/]";

bool IsValidIdentifier(const std::string& str)
{
	return ParseString(str, "^" + PATTERN_IDENTIFIER + "$");
}

} // namespace

CCalculatorController::CCalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_calculator(calculator)
	, m_actionMap({ { "var", std::bind(&CCalculatorController::DeclareVariable, this, std::placeholders::_1) },
		  { "let", std::bind(&CCalculatorController::LetVariable, this, std::placeholders::_1) },
		  { "printvars", std::bind(&CCalculatorController::PrintVars, this, std::placeholders::_1) },
		  { "fn", std::bind(&CCalculatorController::InitFunction, this, std::placeholders::_1) },
		  { "printfns", std::bind(&CCalculatorController::PrintFns, this, std::placeholders::_1) },
		  { "print", std::bind(&CCalculatorController::PrintId, this, std::placeholders::_1) } })
{
}

bool CCalculatorController::HandleCommand()
{
	try
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
	catch (const std::exception& err)
	{
		std::cerr << err.what() << "\n";
	}

	return true;
}

void CCalculatorController::DeclareVariable(std::istream& args)
{
	std::string str;
	args >> str;

	if (!IsValidIdentifier(str))
	{
		m_output << "'" << str << "' is not identifier\n";
	}
	else
	{
		m_output << "Declare variable " << (m_calculator.DeclareVariable(str) ? "success" : "failed") << "\n";
	}
}

void CCalculatorController::LetVariable(std::istream& args)
{
	std::string str;

	args >> str;

	std::string identifier;
	std::string valueStr;

	if (!ParseStr(str, identifier, valueStr))
	{
		m_output << "invalid value\n";
	}
	else
	{
		m_output << "Init varibale ";

		if (IsDouble(valueStr))
		{
			m_output << (m_calculator.LetVariable(identifier, stod(valueStr)) ? "success" : "failed") << "\n";
		}
		else if (!IsValidIdentifier(valueStr))
		{
			m_output << "failed\n";
		}
		else
		{
			m_output << (m_calculator.LetVariable(identifier, valueStr) ? "success" : "failed") << "\n";
		}
	}
}

void CCalculatorController::PrintVars(std::istream& args)
{
	m_output << m_calculator.GetValuesOfVariables();
}

bool ParseFunctionValueString(const std::string& valueStr, std::smatch& result)
{
	const std::string REGULAR_EXPRESSION = "^(" + PATTERN_IDENTIFIER + ")(([+| -| *|/])(" + PATTERN_IDENTIFIER + "))?$";
	std::regex pattern(REGULAR_EXPRESSION);

	if (!std::regex_match(valueStr, result, pattern))
	{
		return false;
	}

	return true;
}

void CCalculatorController::InitFunction(std::istream& args)
{
	std::string str;
	args >> str;

	std::string identifier;
	std::string valueStr;

	if (!ParseStr(str, identifier, valueStr))
	{
		m_output << "failed parse function\n";
	}
	else if (!IsValidIdentifier(identifier))
	{
		m_output << "is not identifier\n";
	}
	else
	{
		std::smatch valueData;

		if (!ParseFunctionValueString(valueStr, valueData))
		{
			m_output << "invalid funtion value\n";
		}
		else
		{
			m_output << "Init function " << (InitFunctionValue(identifier, valueData) ? "success" : "failed") << "\n";
		}
	}
}

void CCalculatorController::PrintFns(std::istream& args)
{
	m_output << m_calculator.GetValuesOfFunctions();
}

void CCalculatorController::PrintId(std::istream& args)
{
	std::string identifier;
	args >> identifier;

	double value = 0;
	if (identifier.empty())
	{
		m_output << "identifier cann't be empty\n";
	}
	else if (!m_calculator.GetValueByIdentitifer(identifier, value))
	{
		m_output << "unkown identifier\n";
	}
	else
	{
		m_output << std::fixed << std::setprecision(2) << value << "\n";
	}
}

bool CCalculatorController::ParseStr(const std::string& str, std::string& identifier, std::string& valueStr)
{
	size_t pos = 0;
	size_t findPos = str.find("=");

	if ((findPos = str.find("=")) != std::string::npos)
	{
		identifier = str.substr(pos, findPos - pos);
		valueStr = str.substr(findPos + 1, str.size() - findPos);

		return true;
	}

	return false;
}

bool CCalculatorController::InitFunctionValue(const std::string& identifier, const std::smatch& valueData)
{
	std::string firstIdentifier = valueData[1];

	if (valueData[4] == "")
	{
		return m_calculator.InitFunction(identifier, firstIdentifier);
	}

	std::string operation = valueData[4];
	std::string secondIdentifier = valueData[5];

	return m_calculator.InitFunction(identifier, firstIdentifier, operation, secondIdentifier);
}
