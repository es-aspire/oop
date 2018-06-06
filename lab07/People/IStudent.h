#pragma once
#include "IPerson.h"

class IStudent : public IPerson
{
public:
	virtual std::string GetHighSchoolName() const = 0;
	virtual void SetHighSchoolName(std::string const& highSchoolName) = 0;

	virtual std::string GetStudentCardNumber() const = 0;
	virtual void SetStudentCardNumber(std::string const& studentCardNumber) = 0;
};
