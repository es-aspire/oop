#include "stdafx.h"
#include "Math.h"

std::ostream& operator<< (std::ostream & output, EquationRoot3 const& equationRoot3)
{
	int i = 1;

	for (double root : equationRoot3.roots)
	{
		output << "x" << i << " = " << root << "\n";
		++i;
	}

	return output;
}

std::ostream& operator<< (std::ostream & output, EquationRoot4 const& equationRoot4)
{
	int i = 1;

	for (double root : equationRoot4.roots)
	{
		output << "x" << i << " = " << root << "\n";
		++i;
	}

	return output;
}
