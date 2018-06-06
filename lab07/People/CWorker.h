#pragma once
#include "CPersonImpl.h"
#include "IWorker.h"

class CWorker : public CPersonImpl<IWorker>
{
public:
	CWorker(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address,
		std::string const& speciality);

	std::string GetSpeciality() const override;
	void SetSpeciality(std::string const& specility) override;

private:
	std::string m_speciality;
};
