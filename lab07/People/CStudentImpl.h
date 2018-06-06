#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address,
		std::string const& highSchoolName,
		std::string const& studentCardNumber);

	std::string GetHighSchoolName() const override;
	void SetHighSchoolName(std::string const& highSchoolName) override;

	std::string GetStudentCardNumber() const override;
	void SetStudentCardNumber(std::string const& studentCardNumber) override;

private:
	std::string m_highSchoolName;
	std::string m_studentCardNumber;
};

template <typename Base>
CStudentImpl<Base>::CStudentImpl(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName,
	std::string const& address,
	std::string const& highSchoolName,
	std::string const& studentCardNumber)
	: CPersonImpl<Base>(firstName, lastName, middleName, address)
	, m_highSchoolName(highSchoolName)
	, m_studentCardNumber(studentCardNumber)
{
}

template <typename Base>
std::string CStudentImpl<Base>::GetHighSchoolName() const
{
	return m_highSchoolName;
}

template <typename Base>
void CStudentImpl<Base>::SetHighSchoolName(std::string const& highSchoolName)
{
	m_highSchoolName = highSchoolName;
}

template <typename Base>
std::string CStudentImpl<Base>::GetStudentCardNumber() const
{
	return m_studentCardNumber;
}

template <typename Base>
void CStudentImpl<Base>::SetStudentCardNumber(std::string const& studentCardNumber)
{
	m_studentCardNumber = studentCardNumber;
}
