#pragma once

class IPerson
{
	virtual std::string GetFirstName() const = 0;
	virtual void SetFirstName(std::string const& firstName) = 0;

	virtual std::string GetLastName() const = 0;
	virtual void SetLastName(std::string const& lastName) = 0;

	virtual std::string GetMiddleName() const = 0;
	virtual void SetMiddleName(std::string const& middleName) = 0;

	virtual std::string GetAddress() const = 0;
	virtual void SetAddress(std::string const& address) = 0;
};
