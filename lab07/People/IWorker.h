#pragma once
#include "IPerson.h"

class IWorker : public IPerson
{
public:
	virtual std::string GetSpeciality() const = 0;
	virtual void SetSpeciality(std::string const& speciality) = 0;
};
