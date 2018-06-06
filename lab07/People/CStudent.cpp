#include "stdafx.h"
#include "CStudent.h"

CStudent::CStudent(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName,
	std::string const& address,
	std::string const& highSchoolName,
	std::string const& studentCardNumber)
	: CStudentImpl<IStudent>(firstName, lastName, middleName, address, highSchoolName, studentCardNumber)
{
}