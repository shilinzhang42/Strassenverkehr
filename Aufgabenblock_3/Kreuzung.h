#pragma once
#include "AktivesVO.h"
#include "Weg.h"
#include <list>
#include <string>

using namespace std;

class Kreuzung :
	public AktivesVO
{
public:
	Kreuzung() : AktivesVO(), p_dTankstelle(0) {}
	Kreuzung(const string& sName, double dTankstelle);
	virtual ~Kreuzung();

	void vVerbinde(const string& sHin, const string& sRueck, double dLaenge, Kreuzung* pZiel, Weg::Begrenzung eLimit = Weg::Autobahn, bool bUeberholverbot = true);
	void vTanken(Fahrzeug* pFzg);
	void vAnnahme(Fahrzeug* pFzg, double dStartZeit);
	virtual void vAbfertigung();
	void vZeichnen();

	virtual ostream& ostreamAusgabe(ostream& os) const;
	virtual istream& istreamEingabe(istream& is);

	Weg* pZufaelligerWeg(Weg* pWeg);
private:
	double p_dTankstelle;
	list<Weg*> p_pWege;
};

