#pragma once
#include "ICar.h"
#include "IPerson.h"
#include <vector>

class 
	ITaxi : public ICar<IPerson>
{
public:
	void Init(size_t value)
	{
		std::vector<size_t> val;
	
 		m_value = value;
	}

private:
	size_t m_value;

};