#pragma once
#include "IBasicVehicle.h"
#include <memory>

template <typename Passenger>
class IVehicle : public IBasicVehicle
{
public:
	virtual void AddPassenger(std::shared_ptr<Passenger> const& Passanger) const = 0;
	virtual Passenger const& GetPessanger(size_t index) const = 0;
	virtual RemovePassenger(size_t index) const = 0;
};

