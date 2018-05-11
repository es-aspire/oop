#pragma once

#include "CalculateOperation.h"

class CCalculator
{
public:
	CCalculator();
	bool DeclareVariable(const std::string& identifier);
	bool LetVariable(const std::string& identifier, double value);
	bool LetVariable(const std::string& identifier, const std::string& valueIdentifier);
	std::string GetValuesOfVariables();

	bool InitFunction(const std::string& identifier, const std::string& firstOperand, const std::string& operation, const std::string& secondOperand);
	bool InitFunction(const std::string& identifier, const std::string& valueStr);
	std::string GetValuesOfFunctions();
	bool GetValueByIdentitifer(const std::string& identifier, double& value);

private:
	bool IsIdentifierExist(const std::string& identifier) const;
	bool IsIdentifierNotExist(const std::string& identifier) const;
	bool IsVariableExist(const std::string& identifier) const;
	bool IsFunctionExist(const std::string& identifier) const;

	bool LetVariableValue(const std::string& identifier, double value);
	double CalcValue(const std::string& identifier);
	
	struct FunctionData
	{
		std::string firstIdentifier;
		std::string secondIdentifier;
		std::string operation;
	};

private:
	using Variables = std::map<std::string, double>;
	using Functions = std::map<std::string, FunctionData>;

	Variables m_variables;
	Functions m_functions;
	CCalculateOperation m_calcOperation;
};
