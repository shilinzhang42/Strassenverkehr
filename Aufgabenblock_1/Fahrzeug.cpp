#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>

int Fahrzeug::p_iMaxID;
extern double dGlobaleZeit;

Fahrzeug::Fahrzeug()
{
	vInitialisiere();
	//cout << "Neues Fahrzeug: '" << p_sName << "' (" << p_iID << ")" << endl;
}

Fahrzeug::Fahrzeug(const Fahrzeug& other)
{
	vInitialisiere();
	p_sName = other.p_sName;
	p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
}

Fahrzeug::Fahrzeug(const string& sName)
{
	vInitialisiere();
	p_sName = sName;
	//cout << "Neues Fahrzeug: '" << p_sName << "' (" << p_iID << ")" << endl;
}

Fahrzeug::Fahrzeug(const string& sName, const double dMaxGeschwindigkeit)
{
	vInitialisiere();
	p_sName = sName;
	p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;
	//cout << "Neues Fahrzeug: '" << p_sName << "' (" << p_iID << ")" << endl;
}

void Fahrzeug::vInitialisiere()
{
	p_sName = "";
	p_iID = p_iMaxID++;
	p_dMaxGeschwindigkeit = 0.0;
	p_dGesamtStrecke = 0.0;
	p_dGesamtZeit = 0.0;
	p_dZeit = 0.0;
}

Fahrzeug::~Fahrzeug()
{
	//cout << "Fahrzeug entfernt: '" << p_sName << "' (" << p_iID << ")" << endl;
}

void Fahrzeug::vAusgabe() const
{
	ostreamAusgabe(cout);
}

/*Lässt die Uhr laufen. Aktualisiert die Attribute.*/
void Fahrzeug::vAbfertigung()
{
	double dZeitDiff = dGlobaleZeit - p_dZeit; //dZeitdiff immer auf 0.3; p_dZeit anfangs 0, dann 0.3, 0.6, 0.9 ... (aufgabe1), (aufgabe 2 in 0.1)
	if (dZeitDiff == 0.0) return;
	p_dZeit = dGlobaleZeit; //p_dZeit übernimmt den Wert von dGlobalezeit; dGlobaleZeit wird außerhalb der Funktion extern definiert(s.o.)
	p_dGesamtStrecke += dZeitDiff * dGeschwindigkeit(); //p_dMaxGeschwindigkeit
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

ostream& Fahrzeug::ostreamAusgabe(ostream& os) const
{
	os << resetiosflags(ios::right) << setiosflags(ios::left | ios::fixed);
	os << setprecision(1);
	os << setw(4) << p_iID;
	os << setw(7) << p_sName << " : ";

	os << setw(10) << dGeschwindigkeit();
	os << setw(10) << p_dMaxGeschwindigkeit;
	os << setw(10) << p_dGesamtStrecke;

	return os;
}
/*Vergleich zweier Gesamtstrecken unterschiedlicher PKWs*/
bool Fahrzeug::operator<(const Fahrzeug& other) const
{
	return p_dGesamtStrecke < other.p_dGesamtStrecke;
}


Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other)
{
	p_sName = other.p_sName;
	p_iID = other.p_iID;
	p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = other.p_dGesamtStrecke;
	p_dGesamtZeit = other.p_dGesamtZeit;
	p_dZeit = other.p_dZeit;
	return *this;
}

/*Durch operatoren Überladung wird für << ostreamAusgabe aufgerufen.*/
ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug)
{
	return fahrzeug.ostreamAusgabe(os);
}