#pragma once
#include "IPerson.h"

class IPupil : public IPerson
{
public:
	virtual std::string GetSchoolName() const = 0;
	virtual void SetSchoolName(std::string const& schoolName) = 0;

	virtual std::string GetClassNumber() const = 0;
	virtual void SetClassNumber(std::string const& classNumber) = 0;
};
