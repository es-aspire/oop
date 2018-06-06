#pragma once

template <typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(std::string const& firstName,
		std::string const& lastName,
		std::string const& middleName,
		std::string const& address);

	std::string GetFirstName() const override;
	void SetFirstName(std::string const& firstName) override;

	std::string GetLastName() const override;
	void SetLastName(std::string const& lastName) override;

	std::string GetMiddleName() const override;
	void SetMiddleName(std::string const& middleName) override;

	std::string GetAddress() const override;
	void SetAddress(std::string const& address) override;

private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_middleName;
	std::string m_address;
};

template <typename Base>
CPersonImpl<Base>::CPersonImpl(std::string const& firstName,
	std::string const& lastName,
	std::string const& middleName,
	std::string const& address)
	: m_firstName(firstName)
	, m_lastName(lastName)
	, m_middleName(middleName)
	, m_address(address)
{
}

template <typename Base>
std::string CPersonImpl<Base>::GetFirstName() const
{
	return m_firstName;
}

template <typename Base>
void CPersonImpl<Base>::SetFirstName(std::string const& firstName)
{
	m_firstName = firstName;
	m_firstName = m_firstName;
}

template <typename Base>
std::string CPersonImpl<Base>::GetLastName() const
{
	return m_lastName;
}

template <typename Base>
void CPersonImpl<Base>::SetLastName(std::string const& lastName)
{
	m_lastName = lastName;
}

template <typename Base>
std::string CPersonImpl<Base>::GetMiddleName() const
{
	return m_middleName;
}

template <typename Base>
void CPersonImpl<Base>::SetMiddleName(std::string const& middleName)
{
	m_middleName = middleName;
}

template <typename Base>
std::string CPersonImpl<Base>::GetAddress() const
{
	return m_address;
}

template <typename Base>
void CPersonImpl<Base>::SetAddress(std::string const& address)
{
	m_address = address;
}
