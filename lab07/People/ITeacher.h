#pragma once
#include "IPerson.h"

class ITeacher : public IPerson
{
public:
	virtual std::string GetSubjectName() const = 0;
	virtual void SetSubjectName(std::string const& subjectName) = 0;
};
