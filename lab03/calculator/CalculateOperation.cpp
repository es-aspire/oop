#include "stdafx.h"
#include "CalculateOperation.h"

namespace
{
bool IsEqual(double firstNumber, double secondNumber)
{
	return ((firstNumber - secondNumber) < 1E-8);
}
} // namespace

CCalculateOperation::CCalculateOperation()
	: m_operationMap({ { "+", [this](double x, double y) {
							return PerformAddition(x, y);
						} },
		  { "-", [this](double x, double y) {
			   return PerformSubtraction(x, y);
		   } },
		  { "*", [this](double x, double y) {
			   return PerformMultiplication(x, y);
		   } },
		  { "/", [this](double x, double y) {
			   return PerformDevideOperation(x, y);
		   } } })
{
}

double CCalculateOperation::Perform(const std::string& operation, double x, double y)
{
	if (auto it = m_operationMap.find(operation) != m_operationMap.end())
	{
		return m_operationMap[operation](x, y);
	}

	throw std::logic_error("unknow operation '" + operation + "'");
}

double CCalculateOperation::PerformAddition(double x, double y) { return x + y; }
double CCalculateOperation::PerformSubtraction(double x, double y) { return x - y; }
double CCalculateOperation::PerformMultiplication(double x, double y) { return x * y; }
double CCalculateOperation::PerformDevideOperation(double x, double y)
{
	if (IsEqual(y, 0))
	{
		throw std::logic_error("devision by zero");
	}

	return x / y;
}
