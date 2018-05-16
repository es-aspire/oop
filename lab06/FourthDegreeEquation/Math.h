#pragma once

#include "VariantUtils.h"
#include <boost/variant.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <exception>
#include <iostream>
#include <map>
#include <variant>
#define _MATH_DEFINES_DEFINED

struct NotAQuadraticEquation
{
};

using QuadraticEquationRoots = boost::variant<
	std::monostate,
	double,
	std::pair<double, double>,
	NotAQuadraticEquation>;

//Solves the equation of the following kind ax ^ 2 + bx ^ 1 + c = 0
QuadraticEquationRoots Solve2(double a, double b, double c);

bool IsEqual(double lhs, double rhs);
double GetNextDivider(double number, double from);

double GetRealRootOfCubicResolvent(double a, double b, double c, double d);

struct EquationRoot3
{
	void SetRoot(int i, double value);

	double numRoots;
	double roots[3];
};

double Arsinh(double x);
double Arcosh(double x);
int Sgn(double x);

double DegreeToRadian(double deg);

// Solves the equation of the following kind ax^3 + bx^2 + cx + e = 0
// https://ru.wikipedia.org/wiki/Тригонометрическая_формула_Виета
EquationRoot3 Solve3(double a, double b, double c, double e);

struct EquationRoot4
{
	double numRoots;
	double roots[4];
};

double GetXValue(double y, double a);

// Solves the equation of the following kind ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
std::ostream& operator<<(std::ostream& output, EquationRoot3 const& equationRoot3);
std::ostream& operator<<(std::ostream& output, EquationRoot4 const& equationRoot4);
