#include "stdafx.h"
#include "Rational.h"

#include <map>
#include <numeric>

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	else if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	double lhs = m_numerator;
	double rhs = m_denominator;

	return lhs / rhs;
}

CRational::CompoundFraction CRational::ToCompoundFraction() const
{
	int integer = m_numerator / m_denominator;
	int lhs = (m_numerator < 0 && integer != 0) ? -m_numerator : m_numerator;

	CRational properFraction(lhs % m_denominator, m_denominator);

	return std::make_pair(integer, properFraction);
}

void CRational::Normalize()
{
	int gcd = std::gcd(m_numerator, m_denominator);
	if (gcd != INT_MIN)
	{
		m_numerator /= gcd;
		m_denominator /= gcd;
	}
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(CRational const& rational)
{
	*this = *this + rational;
	return *this;
}

CRational& CRational::operator-=(CRational const& rational)
{
	*this += -rational;
	return *this;
}

CRational& CRational::operator*=(CRational const& rational)
{
	*this = *this * rational;
	return *this;
}

CRational& CRational::operator/=(CRational const& rational)
{
	*this = *this / rational;
	return *this;
}

std::ostream& operator<<(std::ostream& output, const CRational::CompoundFraction& fraction)
{
	output << ((fraction.first == 0) ? "" : std::to_string(fraction.first) + " ") << fraction.second;

	return output;
}

std::istream& operator>>(std::istream& input, CRational& rational)
{
	int numerator = 0;
	int denominator = 0;

	if ((input >> numerator) && (input.get() == '/') && (input >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit | input.rdstate());
	}

	return input;
}

std::ostream& operator<<(std::ostream& output, const CRational& rational)
{
	output << rational.GetNumerator() << "/" << rational.GetDenominator();

	return output;
}

CRational const operator+(CRational const& lhs, CRational const& rhs)
{
	int numeratorLhs = lhs.GetNumerator();
	int numeratorRhs = rhs.GetNumerator();
	int denominatorLhs = lhs.GetDenominator();
	int denominatorRhs = rhs.GetDenominator();

	return CRational((numeratorLhs * denominatorRhs + numeratorRhs * denominatorLhs), denominatorLhs * denominatorRhs);
}

CRational const operator-(CRational const& lhs, CRational const& rhs)
{
	return lhs + -rhs;
}

CRational const operator*(CRational const& lhs, CRational const& rhs)
{
	return CRational(lhs.GetNumerator() * rhs.GetNumerator(),
		lhs.GetDenominator() * rhs.GetDenominator());
}

CRational const operator/(CRational const& lhs, CRational const& rhs)
{
	return CRational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
}

bool operator==(CRational const& lhs, CRational const& rhs)
{
	return lhs.GetNumerator() == rhs.GetNumerator()
		&& lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator!=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs == rhs);
}

bool operator<(CRational const& lhs, CRational const& rhs)
{
	return lhs.GetNumerator() * rhs.GetDenominator() < lhs.GetDenominator() * rhs.GetNumerator();
}

bool operator>=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs < rhs);
}

bool operator>(CRational const& lhs, CRational const& rhs)
{
	return rhs < lhs;
}

bool operator<=(CRational const& lhs, CRational const& rhs)
{
	return !(rhs < lhs);
}
