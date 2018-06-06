#include "stdafx.h"
#include "CWorker.h"

CWorker::CWorker(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName,
	std::string const& address,
	std::string const& speciality)
	: CPersonImpl<IWorker>(firstName, lastName, middleName, address)
	, m_speciality(speciality)
{
}

std::string CWorker::GetSpeciality() const
{
	return m_speciality;
}

void CWorker::SetSpeciality(std::string const& specility)
{
	m_speciality = specility;
}