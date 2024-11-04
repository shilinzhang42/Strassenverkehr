#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "FzgFahren.h"
#include "FzgParken.h"
#include "Weg.h"

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug() : AktivesVO()
{
	vInitialisiere();
	//cout << "Neues Fahrzeug: '" << p_sName << "' (" << p_iID << ")" << endl;
}

Fahrzeug::Fahrzeug(const Fahrzeug& other) : AktivesVO(other)
{
	vInitialisiere();
	p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
}

Fahrzeug::Fahrzeug(const string& sName) : AktivesVO(sName)
{
	vInitialisiere();
	//cout << "Neues Fahrzeug: '" << p_sName << "' (" << p_iID << ")" << endl;
}

Fahrzeug::Fahrzeug(const string& sName, const double dMaxGeschwindigkeit) : AktivesVO(sName)
{
	vInitialisiere();
	p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;
	//cout << "Neues Fahrzeug: '" << p_sName << "' (" << p_iID << ")" << endl;
}

void Fahrzeug::vInitialisiere()
{
	p_dMaxGeschwindigkeit = 0.0;
	p_dGesamtStrecke = 0.0;
	p_dAbschnittStrecke = 0.0;
	p_dGesamtZeit = 0.0;
	p_pVerhalten = new FzgFahren(NULL);
}

Fahrzeug::~Fahrzeug()
{
	//cout << "Fahrzeug entfernt: '" << p_sName << "' (" << p_iID << ")" << endl;
	delete p_pVerhalten;
}

/*Lässt die Uhr laufen. Aktualisiert die Attribute.*/
void Fahrzeug::vAbfertigung()
{
	double dZeitDiff = dGlobaleZeit - p_dZeit; //dZeitdiff immer auf 0.3; p_dZeit anfangs 0, dann 0.3, 0.6, 0.9 ... (aufgabe1), (aufgabe 2 in 0.1)
	if (dZeitDiff == 0.0) return;
	p_dZeit = dGlobaleZeit; //p_dZeit übernimmt den Wert von dGlobalezeit; dGlobaleZeit wird außerhalb der Funktion extern definiert(s.o.)

	double dStrecke = p_pVerhalten->dStrecke(this, dZeitDiff);
	p_dGesamtStrecke += dStrecke;
	p_dAbschnittStrecke += dStrecke;
}

double Fahrzeug::dGeschwindigkeit() const
{
	double dGeschwindigkeit = p_dMaxGeschwindigkeit;
	const Weg* weg = p_pVerhalten->getWeg();
	if (weg) {
		switch (weg->getLimit()) {
		case Weg::Innerorts:
			dGeschwindigkeit = min(dGeschwindigkeit, 50.0);
			break;
		case Weg::Landstrasse:
			dGeschwindigkeit = min(dGeschwindigkeit, 100.0);
			break;
		}
	}
	return dGeschwindigkeit;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

void Fahrzeug::vNeueStrecke(Weg* pWeg)
{
	delete p_pVerhalten;
	p_pVerhalten = new FzgFahren(pWeg);
}

void Fahrzeug::vNeueStrecke(Weg* pWeg, double dStartZeit)
{
	delete p_pVerhalten;
	p_pVerhalten = new FzgParken(pWeg, dStartZeit);
}

ostream& Fahrzeug::ostreamAusgabe(ostream& os) const
{
	AktivesVO::ostreamAusgabe(os);
	os << setw(10) << dGeschwindigkeit();
	os << setw(10) << p_dMaxGeschwindigkeit;
	os << setw(10) << p_dAbschnittStrecke;
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
	AktivesVO::operator=(other);
	p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = other.p_dGesamtStrecke;
	p_dGesamtZeit = other.p_dGesamtZeit;
	p_dZeit = other.p_dZeit;
	return *this;
}

double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}