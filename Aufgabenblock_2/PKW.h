#pragma once
#include "Fahrzeug.h"
#include <string>

class PKW :
	public Fahrzeug
{
public:
	PKW();
	PKW(const PKW& other);
	PKW(const string& sName);
	PKW(const string& sName, const double dMaxGeschwindigkeit);
	PKW(const string& sName, const double dMaxGeschwindigkeit, double dVerbrauch);
	PKW(const string& sName, const double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen);
	virtual ~PKW();

	virtual void vAbfertigung();

	virtual ostream& ostreamAusgabe(ostream& os) const;

	virtual double dTanken(double dMenge = -1.0);
	PKW& operator=(const PKW& other);

	virtual void vZeichnen(const Weg* pWeg) const;
private:
	double p_dVerbrauch, p_dTankinhalt, p_dTankvolumen, p_dGesamtVerbrauch;
	void vInitialisiere();
protected:
	
};

