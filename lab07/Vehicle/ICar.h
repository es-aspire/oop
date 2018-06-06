#pragma once
#include "IVehicle.h"

enum MakeOfTheCar
{
	BMW,
	MITSHUBISHI,
	FORD,
	MERSEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSHE,
	LEXUS,
	NISSAN,
	INFINITI
};

template <typename Passenger>
class ICar :
	public IVehicle<Passenger>
{
public:
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
};

