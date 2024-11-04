#pragma once
#include <string>
#include "AktivesVO.h"

using namespace std;
class FzgVerhalten;
class Weg;

class Fahrzeug : public AktivesVO
{
public:
	Fahrzeug();
	Fahrzeug(const Fahrzeug& other);
	Fahrzeug(const string& sName);
	Fahrzeug(const string& sName, const double dMaxGeschwindigkeit);
	virtual ~Fahrzeug();

	virtual void vAbfertigung();
	virtual double dGeschwindigkeit() const;

	virtual double dTanken(double dMenge = -1.0);

	void vNeueStrecke(Weg* pWeg);
	void vNeueStrecke(Weg* pWeg, double dStartzeit);

	virtual ostream& ostreamAusgabe(ostream& os) const;
	virtual istream& istreamEingabe(istream& is);

	bool operator<(const Fahrzeug& other) const; //innerhalb der Klasse: linker Operand = this Zeiger , Rechter Operand = Parameter
	
	Fahrzeug& operator=(const Fahrzeug& other);

	double getAbschnittStrecke() const;

	virtual void vZeichnen(const Weg* pWeg) const{}

	FzgVerhalten* getVerhalten();
private:
	double p_dGesamtZeit, p_dAbschnittStrecke;

	FzgVerhalten* p_pVerhalten;

	void vInitialisiere();

protected:
	double p_dGesamtStrecke, p_dMaxGeschwindigkeit;
};
