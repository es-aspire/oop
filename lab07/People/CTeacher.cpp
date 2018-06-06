#include "stdafx.h"
#include "CTeacher.h"

CTeacher::CTeacher(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName,
	std::string const& address,
	std::string const& subjectName)
	: CPersonImpl<ITeacher>(firstName, lastName, middleName, address)
	, m_subjectName(subjectName)
{
}

std::string CTeacher::GetSubjectName() const
{
	return m_subjectName;
}

void CTeacher::SetSubjectName(std::string const& subjectName)
{
	m_subjectName = subjectName;
}
