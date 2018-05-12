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
inline QuadraticEquationRoots Solve2(double a, double b, double c)
{
	if (std::abs(a) < std::numeric_limits<double>::epsilon())
	{
		return NotAQuadraticEquation{};
	}

	auto disc = b * b - 4 * a * c;

	if (disc < 0)
	{
		return std::monostate{};
	}

	if (disc < std::numeric_limits<double>::epsilon())
	{
		return -b / (2 * a);
	}

	auto sqrtDisc = sqrt(disc);
	return std::make_pair((-b - sqrtDisc) / (2 * a), (-b + sqrtDisc) / (2 * a));
}

inline bool IsEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) < std::numeric_limits<double>::epsilon();
}

inline double GetNextDivider(double number, double from)
{
	for (int i = static_cast<int>(from); i <= std::abs(number); ++i)
	{
		if (IsEqual(std::fmod(number, i), 0.0))
		{
			return i;
		}
	}

	return std::numeric_limits<double>::quiet_NaN();
}

inline double GetRealRootOfCubicResolvent(double a, double b, double c, double d)
{
	for (int i = 1; i <= std::abs(d); ++i)
	{
		if (IsEqual(fmod(d, i), 0.0))
		{
			double s = (d < 0) ? -i : i;
			double a1 = a * s * s * s;
			double b1 = b * s * s;
			double c1 = c * s;
			double sum = a1 + b1 + c1 + d;

			if (IsEqual(sum, 0.0))
			{
				return s;
			}
		}
	}
	return std::numeric_limits<double>::quiet_NaN();
}

struct EquationRoot3
{
	void SetRoot(int i, double value)
	{
		roots[i] = value;
	}

	double numRoots;
	double roots[3];
};

inline double Arsinh(double x)
{
	return log(x + sqrt(x * x + 1));
}

inline double Arcosh(double x)
{
	if (x < 1.0)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	return log(x + sqrt(x * x - 1));
}

inline int Sgn(double x)
{
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

inline double DegreeToRadian(double deg)
{
	return (deg * M_PI / 180);
}

// Solves the equation of the following kind ax^3 + bx^2 + cx + e = 0
// https://ru.wikipedia.org/wiki/Тригонометрическая_формула_Виета
inline EquationRoot3 Solve3(double a, double b, double c, double e)
{
	if (IsEqual(a, 0.0))
	{
		throw std::logic_error("a in  ax^3 + bx^2 + cx + e = 0 can't be empty");
	}

	double devide = a;
	a = b / devide;
	b = c / devide;
	c = e / devide;

	double Q = (a * a - 3 * b) / 9.0;
	double R = (2 * a * a * a - 9 * a * b + 27 * c) / 54.0;
	double S = Q * Q * Q - R * R;

	EquationRoot3 result;

	if (S > 0) // три действительных корня
	{
		double fi = acos(R / sqrt(Q * Q * Q)) / 3;

		result.roots[0] = (-2 * sqrt(Q) * cos(fi)) - a / 3;
		result.roots[1] = (-2 * sqrt(Q) * cos(fi + 2 * M_PI / 3)) - a / 3;
		result.roots[2] = (-2 * sqrt(Q) * cos(fi - 2 * M_PI / 3)) - a / 3;
		result.numRoots = 3;
	}

	else if (S < 0)
	{
		if (Q > 0) // один действительный корень
		{
			double fi = Arcosh(std::abs(R) / sqrt(Q * Q * Q)) / 3;

			result.roots[0] = -2 * Sgn(R) * sqrt(Q) * cosh(fi) - a / 3;
			result.roots[1] = std::numeric_limits<double>::quiet_NaN();
			result.roots[2] = std::numeric_limits<double>::quiet_NaN();
			result.numRoots = 3;
		}
		else if (Q < 0)
		{
			double fi = Arsinh(std::abs(R) / sqrt(std::abs(Q*Q*Q))) / 3;

			result.roots[0] = -2 * Sgn(R) * sqrt(std::abs(Q))*sinh(fi) - a / 3;
			result.roots[1] = std::numeric_limits<double>::quiet_NaN();
			result.roots[2] = std::numeric_limits<double>::quiet_NaN();
			result.numRoots = 3;
		}
		else
		{
			double number = c - a * a * a / 27.0;

			result.roots[0] = -1 * pow(number, 1 / 3) - a / 3;
			result.roots[1] = std::numeric_limits<double>::quiet_NaN();
			result.roots[2] = std::numeric_limits<double>::quiet_NaN();
			result.numRoots = 3;
		}
	}
	else // уравнение вырождено и имеет меньше 3 различных решений (второй корень кратности 2):
	{
		result.roots[0] = -2 * Sgn(R) * sqrt(Q) - a / 3;
		result.roots[1] = Sgn(R) * sqrt(Q) - a / 3;
		result.roots[2] = std::numeric_limits<double>::quiet_NaN();
		result.numRoots = 3;
	}

	return result;
}

struct EquationRoot4
{
	double numRoots;
	double roots[4];
};

inline double GetXValue(double y, double a)
{
	return y - a / 4.0;
}

// Solves the equation of the following kind ax^4 + bx^3 + cx^2 + dx + e = 0
inline EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (IsEqual(a, 0.0))
	{
		throw std::invalid_argument("A zero coefficinet value is not allowed for x4");
	}

	double A = b / a;
	double B = c / a;
	double C = d / a;
	double D = e / a;

	double p = B - 3.0 * A * A / 8.0;
	double q = A * A * A / 8.0 - A * B / 2.0 + C;
	double r = -3 * A * A * A * A / 256.0 + A * A * B / 16.0 - A * C / 4.0 + D;

	double ACubicResolvent = 2.0;
	double BCubicResolvent = -p;
	double CCubicResolvent = -2 * r;
	double DCubicResolvent = r * p - q * q / 4.0;

	EquationRoot3 solve3 = Solve3(ACubicResolvent, BCubicResolvent, CCubicResolvent, DCubicResolvent);

	double realRootOfCubicResolvent = solve3.roots[0];
	double a2 = 1.0;
	double b2 = -sqrt(2 * realRootOfCubicResolvent - p);
	double c2 = q / (2 * -b2) + realRootOfCubicResolvent;

	auto result1 = Solve2(a2, b2, c2);

	EquationRoot4 equationRoot4;
	if (auto singleRoot = VeriantUtills::get_if<double>(&result1))
	{
		equationRoot4.roots[0] = GetXValue(*singleRoot, A);
		equationRoot4.roots[1] = std::numeric_limits<double>::quiet_NaN();
		++equationRoot4.numRoots;
	}
	else if (auto twoRoots = VeriantUtills::get_if<std::pair<double, double>>(&result1))
	{
		equationRoot4.roots[0] = GetXValue(twoRoots->first, A);
		equationRoot4.roots[1] = GetXValue(twoRoots->second, A);
		equationRoot4.numRoots += 2;
	}

	double a3 = 1.0;
	double b3 = sqrt(2 * realRootOfCubicResolvent - p);
	double c3 = -q / (2 * b3) + realRootOfCubicResolvent;

	auto result2 = Solve2(a3, b3, c3);

	if (auto singleRoot = VeriantUtills::get_if<double>(&result2))
	{
		equationRoot4.roots[2] = GetXValue(*singleRoot, A);
		equationRoot4.roots[3] = std::numeric_limits<double>::quiet_NaN();
		++equationRoot4.numRoots;
	}
	else if (auto twoRoots = VeriantUtills::get_if<std::pair<double, double>>(&result2))
	{
		equationRoot4.roots[2] = GetXValue(twoRoots->first, A);
		equationRoot4.roots[3] = GetXValue(twoRoots->second, A);
		equationRoot4.numRoots += 2;
	}

	return equationRoot4;
}

std::ostream& operator<<(std::ostream& output, EquationRoot3 const& equationRoot3);
std::ostream& operator<<(std::ostream& output, EquationRoot4 const& equationRoot4);
