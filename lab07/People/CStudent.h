#pragma once
#include "CStudentImpl.h"
#include "IStudent.h"

class CStudent : public CStudentImpl<IStudent>
{
public:
	CStudent(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address,
		std::string const& highSchoolName,
		std::string const& studentCardNumber);
};
