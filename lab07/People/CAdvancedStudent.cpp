#include "stdafx.h"
#include "CAdvancedStudent.h"

CAdvancedStudent::CAdvancedStudent(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName,
	std::string const& address,
	std::string const& highSchoolName,
	std::string const& studentCardNumber,
	std::string const& dissertationTopic)
	: CStudentImpl<IAdvancedStudent>(firstName, lastName, middleName, address, highSchoolName, studentCardNumber)
	, m_dissertationTopic(dissertationTopic)
{
}

std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}

void CAdvancedStudent::SetDissertationTopic(std::string const& dissertationTopic)
{
	m_dissertationTopic = dissertationTopic;
}
