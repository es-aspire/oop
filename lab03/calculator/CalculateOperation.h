#pragma once
#include <functional>
#include <map>

class CCalculateOperation
{
public:
	CCalculateOperation();
	double Perform(const std::string& operation, double x, double y);

private:
	double PerformAddition(double x, double y);
	double PerformSubtraction(double x, double y);
	double PerformMultiplication(double x, double y);
	double PerformDevideOperation(double x, double y);

private:
	using OperationMap = std::map<std::string, std::function<double(double x, double y)>>;

	OperationMap m_operationMap;
};
