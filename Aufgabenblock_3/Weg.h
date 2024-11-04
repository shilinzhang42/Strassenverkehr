#pragma once
#include "AktivesVO.h"
#include "LazyListe.h"
#include <string>

using namespace std;

class Fahrzeug;
class Kreuzung;

class Weg :
	public AktivesVO
{
public:
	static enum Begrenzung {Innerorts, Landstrasse, Autobahn};
	Weg();
	Weg(const string& sName, double dLaenge, Begrenzung eLimit = Autobahn, bool bUeberholverbot = true);
	~Weg();

	virtual void vAbfertigung();

	void vZeichnen();

	virtual ostream& ostreamAusgabe(ostream& os) const;

	double getLaenge() const;

	void vAnnahme(Fahrzeug* pFzg);
	void vAnnahme(Fahrzeug* pFzg, double dStartzeit);

	void vAbgabe(Fahrzeug* pFzg);

	Begrenzung getLimit() const;

	double getSchranke() const;
	void setSchranke(double dSchranke);

	void setRueck(Weg* pRueck);
	Weg* getRueck();
	void setZiel(Kreuzung* pZiel);
	Kreuzung* getZiel();

private:
	bool p_bUeberholverbot;
	double p_dLaenge, p_dSchranke;
	Begrenzung p_eLimit;
	LazyListe<Fahrzeug*> p_pFahrzeuge;

	Weg* p_pRueck;
	Kreuzung* p_pZielKreuzung;
};

