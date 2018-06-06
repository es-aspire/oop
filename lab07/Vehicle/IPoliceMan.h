#pragma once
#include "IPerson.h"

class IPoliceMan : public IPerson
{
public:
	virtual std::string GetDepartamentName() const = 0;
};