#include "stdafx.h"
#include "CPupil.h"

CPupil::CPupil(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName, 
	std::string const& address,
	std::string const& schoolName, 
	std::string const& classNumber)
	: CPersonImpl<IPupil>(firstName, lastName, middleName, address)
	, m_schoolName(schoolName)
	, m_classNumber(classNumber)
{
}

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

void CPupil::SetSchoolName(std::string const& schoolName)
{
	m_schoolName = schoolName;
}

std::string CPupil::GetClassNumber() const
{
	return m_classNumber;
}

void CPupil::SetClassNumber(std::string const& classNumber)
{
	m_classNumber = classNumber;
}