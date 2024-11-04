#include "PKW.h"
#include "Weg.h"
#include "SimuClient.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;
extern double dGlobaleZeit;


PKW::PKW() : Fahrzeug()
{
	vInitialisiere();
}
/*Copy-Constructor, setzt mit vInitialisiere von PKW auf die entsprechenden Werte, zusätzlich wird Verbrauch und Tankvolumen von
**other übernommen*/
PKW::PKW(const PKW& other) : Fahrzeug(other)
{
	vInitialisiere();
	p_dVerbrauch = other.p_dVerbrauch;
	p_dTankvolumen = other.p_dTankvolumen;
	p_dTankinhalt = 0.5 * p_dTankvolumen;
}



PKW::PKW(const string& sName) : Fahrzeug(sName)
{
	vInitialisiere();
}

PKW::PKW(const string& sName, const double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit)
{
	vInitialisiere();
}

PKW::PKW(const string& sName, const double dMaxGeschwindigkeit, double dVerbrauch) : Fahrzeug(sName, dMaxGeschwindigkeit)
{
	vInitialisiere();
	p_dVerbrauch = dVerbrauch;
}

PKW::PKW(const string& sName, const double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) : Fahrzeug(sName, dMaxGeschwindigkeit)
{
	vInitialisiere();
	p_dVerbrauch = dVerbrauch;
	p_dTankvolumen = dTankvolumen;
	p_dTankinhalt = 0.5 * p_dTankvolumen;
}


PKW::~PKW()
{
}

/*Jeder PKW wird mit einem Verbrauch von 10.0, einem Tankvolumen 551.0 , die hälfte des Tankvolumens als Tankinhalt und der Verbrauch
**wird durch die eingabe initialisiert.*/
void PKW::vInitialisiere()
{
	p_dVerbrauch = 10.0; 
	p_dTankvolumen = 55.0;
	p_dTankinhalt = 0.5 * p_dTankvolumen;
	p_dGesamtVerbrauch = 0.0;
}

double PKW::dTanken(double dMenge)
{
	if (dMenge < 0.0) {
		dMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dMenge;
	} else {
		dMenge = min(dMenge, p_dTankvolumen - p_dTankinhalt);
		p_dTankinhalt += dMenge;
		return dMenge;
	}
}

ostream& PKW::ostreamAusgabe(ostream& os) const
{
	Fahrzeug::ostreamAusgabe(os);
	os << setprecision(1);
	os << setw(7) << p_dTankinhalt;// << "/" << p_dTankvolumen;
	os << setw(10) << p_dGesamtVerbrauch;
	return os;
}

istream& PKW::istreamEingabe(istream& is)
{
	Fahrzeug::istreamEingabe(is);
	is >> p_dVerbrauch >> p_dTankvolumen;
	p_dTankinhalt = 0.5*p_dTankvolumen;
	return is;
}

void PKW::vAbfertigung()
{
	if (p_dTankinhalt < 0.0) return;
	double dZeitDiff = dGlobaleZeit - p_dZeit;//p_dZeit anfangs 0, dann 0.1, 0.2, 0.3, ... Globalezeit 0.1, 0.2, 0.3, 0.4 , ->dZeitDiff = 0.1
	double dVerbrauch = dZeitDiff * p_dVerbrauch;
	p_dTankinhalt -= dVerbrauch;
	if (p_dTankinhalt < 0.0) p_dTankinhalt = 0.0;
	p_dGesamtVerbrauch += dVerbrauch; //TODO: checken ob hier nur differenz addiert werde soll
	Fahrzeug::vAbfertigung();
}

PKW& PKW::operator=(const PKW& other)
{
	Fahrzeug::operator=(other);
	p_dVerbrauch = other.p_dVerbrauch; 
	p_dTankvolumen = other.p_dTankvolumen;
	p_dTankinhalt = other.p_dTankinhalt;
	p_dGesamtVerbrauch = other.p_dGesamtVerbrauch;
	return *this;
}

void PKW::vZeichnen(const Weg* pWeg) const
{
	bZeichnePKW(getName().c_str(), pWeg->getName().c_str(), getAbschnittStrecke() / pWeg->getLaenge(), dGeschwindigkeit(), p_dTankinhalt);
}