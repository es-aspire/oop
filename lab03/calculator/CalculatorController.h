#pragma once
#include <map>

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	void DeclareVariable(std::istream& args);
	void LetVariable(std::istream& args);
	void PrintVars(std::istream& args);
	
	void InitFunction(std::istream& args);
	void PrintFns(std::istream& args);
	void PrintId(std::istream& args);
	
	bool ParseStr(const std::string& str, std::string& identifier, std::string& valueStr);
	bool InitFunctionValue(const std::string& identifier, const std::smatch& valueData);

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream& args)>>;

	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	CCalculator& m_calculator;
};
