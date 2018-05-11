#pragma once

class CRational
{
public:

	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	void Normalize();

	using CompoundFraction = std::pair<int, CRational>;

	CompoundFraction ToCompoundFraction() const;

	CRational const operator+() const;
	CRational const operator-() const;
	CRational& operator+=(CRational const& rational);
	CRational& operator-=(CRational const& rational);
	CRational& operator*=(CRational const& rational);
	CRational& operator/=(CRational const& rational);

private:
	int m_numerator;
	int m_denominator;
};

std::ostream& operator<<(std::ostream& output, const CRational::CompoundFraction& fraction);
std::istream& operator>>(std::istream& input, CRational& rational);
std::ostream& operator<<(std::ostream& output, const CRational& rational);

CRational const operator+(CRational const& lhs, CRational const& rhs);
CRational const operator-(CRational const& lhs, CRational const& rhs);
CRational const operator*(CRational const& lhs, CRational const& rhs);
CRational const operator/(CRational const& lhs, CRational const& rhs);
bool operator==(CRational const& lhs, CRational const& rhs);
bool operator!=(CRational const& lhs, CRational const& rhs);
bool operator<(CRational const& lhs, CRational const& rhs);
bool operator>=(CRational const& lhs, CRational const& rhs);
bool operator>(CRational const& lhs, CRational const& rhs);
bool operator<=(CRational const& lhs, CRational const& rhs);
