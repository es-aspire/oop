#pragma once
#include "CPersonImpl.h"
#include "ITeacher.h"

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	CTeacher(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address,
		std::string const& subjectName);

	std::string GetSubjectName() const override;
	void SetSubjectName(std::string const& subjectName) override;

private:
	std::string m_subjectName;
};
