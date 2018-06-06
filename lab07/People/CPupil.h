#pragma once
#include "CPersonImpl.h"
#include "IPupil.h"

class CPupil : public CPersonImpl<IPupil>
{
public:
	CPupil(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address,
		std::string const& schoolName,
		std::string const& classNumber);

	std::string GetSchoolName() const override;
	void SetSchoolName(std::string const& schoolName) override;

	std::string GetClassNumber() const override;
	void SetClassNumber(std::string const& classNumber) override;

private:
	std::string m_schoolName;
	std::string m_classNumber;
};
