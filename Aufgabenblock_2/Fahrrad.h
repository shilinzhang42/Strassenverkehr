#pragma once
#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad() : Fahrzeug() {}
	Fahrrad(const Fahrrad& other) : Fahrzeug(other) {}
	Fahrrad(const string& sName) : Fahrzeug(sName) {}
	Fahrrad(const string& sName, const double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit) {}
	virtual ~Fahrrad();

	virtual double dGeschwindigkeit() const;
	virtual void vZeichnen(const Weg* pWeg) const;
};

