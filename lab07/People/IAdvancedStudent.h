#pragma once
#include "IStudent.h"

class IAdvancedStudent : public IStudent
{
public:
	virtual std::string GetDissertationTopic() const = 0;
	virtual void SetDissertationTopic(std::string const& dissertationTopic) = 0;
};
