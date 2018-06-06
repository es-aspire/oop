#pragma once
#include "CStudentImpl.h"
#include "IAdvancedStudent.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address,
		std::string const& highSchoolName,
		std::string const& studentCardNumber,
		std::string const& dissertationTopic);

	std::string GetDissertationTopic() const;
	void SetDissertationTopic(std::string const& dissertationTopic);

private:
	std::string m_dissertationTopic;
};
