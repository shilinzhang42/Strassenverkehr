#pragma once
#include "AktivesVO.h"
#include "LazyListe.h"
#include <string>

using namespace std;

class Fahrzeug;

class Weg :
	public AktivesVO
{
public:
	static enum Begrenzung {Innerorts, Landstrasse, Autobahn};
	Weg();
	Weg(const string& sName, double dLaenge, Begrenzung eLimit = Autobahn);
	~Weg();

	virtual void vAbfertigung();

	virtual ostream& ostreamAusgabe(ostream& os) const;

	double getLaenge() const;

	void vAnnahme(Fahrzeug* pFzg);
	void vAnnahme(Fahrzeug* pFzg, double dStartzeit);

	void vAbgabe(Fahrzeug* pFzg);

	Begrenzung getLimit() const;

private:
	double p_dLaenge;
	Begrenzung p_eLimit;
	LazyListe<Fahrzeug*> p_pFahrzeuge;

};

