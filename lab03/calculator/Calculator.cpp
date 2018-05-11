#include "stdafx.h"
#include "Calculator.h"
#include <limits>
#include <regex>

CCalculator::CCalculator()
{
}

bool CCalculator::DeclareVariable(const std::string& identifier)
{
	if (identifier.empty() || IsIdentifierExist(identifier))
	{
		return false;
	}

	m_variables.emplace(identifier, std::numeric_limits<double>::quiet_NaN());

	return true;
}

bool CCalculator::LetVariable(const std::string& identifier, double value)
{ 
	return LetVariableValue(identifier, value);
}

bool CCalculator::LetVariable(const std::string& identifier, const std::string& valueIdentifier)
{
	return LetVariableValue(identifier, CalcValue(valueIdentifier));
}

std::string CCalculator::GetValuesOfVariables()
{
	std::stringstream strm;
	strm << std::fixed << std::setprecision(2);

	for (const auto& variable : m_variables)
	{
		strm << variable.first << ":" << variable.second << "\n";
	}

	return strm.str();
}

bool CCalculator::InitFunction(const std::string& identifier, const std::string& firstOperand, const std::string& operation, const std::string& secondOperand)
{
	if (IsVariableExist(identifier) || IsIdentifierNotExist(firstOperand) || IsIdentifierNotExist(secondOperand))
	{
		return false;
	}

	FunctionData functionData;
	functionData.firstIdentifier = firstOperand;
	functionData.operation = operation;
	functionData.secondIdentifier = secondOperand;

	m_functions.emplace(identifier, functionData);

	return true;
}

bool CCalculator::InitFunction(const std::string& identifier, const std::string& variableIdentifier)
{
	if (IsVariableExist(identifier) || IsIdentifierNotExist(variableIdentifier))
	{
		return false;
	}

	FunctionData functionData;
	functionData.firstIdentifier = variableIdentifier;

	m_functions.emplace(identifier, functionData);

	return true;
}

std::string CCalculator::GetValuesOfFunctions()
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);

	for (const auto& item : m_functions)
	{
		strm << item.first << ":" << CalcValue(item.first) << "\n";
	}

	return strm.str();
}

bool CCalculator::GetValueByIdentitifer(const std::string& identifier, double& value)
{
	if (!IsIdentifierExist(identifier))
	{
		return false;
	}

	value = CalcValue(identifier);

	return true;
}

bool CCalculator::IsIdentifierExist(const std::string& identifier) const
{
	return IsVariableExist(identifier) || IsFunctionExist(identifier);
}

bool CCalculator::IsIdentifierNotExist(const std::string& identifier) const
{
	return !IsVariableExist(identifier) && !IsFunctionExist(identifier);
}

bool CCalculator::IsFunctionExist(const std::string& identifier) const
{
	return m_functions.find(identifier) != m_functions.end();
}

bool CCalculator::IsVariableExist(const std::string& identifier) const
{
	return m_variables.find(identifier) != m_variables.end();
}

bool CCalculator::LetVariableValue(const std::string& identifier, double value)
{
	if (IsFunctionExist(identifier))
	{
		return false;
	}

	if (IsVariableExist(identifier))
	{
		m_variables.at(identifier) = value;
	
		return true;
	}

	m_variables.emplace(identifier, value);
	
	return true;
}

double CCalculator::CalcValue(const std::string& identifier)
{
	double value = 0;

	if (IsVariableExist(identifier))
	{
		return m_variables.at(identifier);
	}

	FunctionData funcData = m_functions.at(identifier);
	double firstIdentifierValue = CalcValue(funcData.firstIdentifier);

	if (funcData.operation.empty())
	{
		return firstIdentifierValue;
	}

	return m_calcOperation.Perform(funcData.operation, firstIdentifierValue, CalcValue(funcData.secondIdentifier));
}
