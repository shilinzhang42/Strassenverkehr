#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "FzgVerhalten.h"

Kreuzung::Kreuzung(const string& sName, double dTankstelle) : AktivesVO(sName), p_dTankstelle(dTankstelle)
{
}


Kreuzung::~Kreuzung()
{
	for (list<Weg*>::iterator it = p_pWege.begin(); it != p_pWege.end(); it++)
		delete *it;
}

void Kreuzung::vVerbinde(const string& sHin, const string& sRueck, double dLaenge, Kreuzung* pZiel, Weg::Begrenzung eLimit, bool bUeberholverbot)
{
	Weg* hin = new Weg(sHin, dLaenge, eLimit, bUeberholverbot);
	Weg* rueck = new Weg(sRueck, dLaenge, eLimit, bUeberholverbot);
	hin->setRueck(rueck);
	rueck->setRueck(hin);
	hin->setZiel(pZiel);
	rueck->setZiel(this);
	p_pWege.push_back(hin);
	pZiel->p_pWege.push_back(rueck);
}

void Kreuzung::vTanken(Fahrzeug* pFzg)
{
	if (p_dTankstelle > 0)
		p_dTankstelle -= pFzg->dTanken();
}

void Kreuzung::vAnnahme(Fahrzeug* pFzg, double dStartZeit)
{
	vTanken(pFzg);
	//p_pWege.front()->vAnnahme(pFzg, dStartZeit);
	if (pFzg->getVerhalten())
		pZufaelligerWeg(pFzg->getVerhalten()->getWeg()->getRueck())->vAnnahme(pFzg, dStartZeit);
	else
		pZufaelligerWeg(NULL)->vAnnahme(pFzg, dStartZeit);
}

void Kreuzung::vAbfertigung()
{
	for (list<Weg*>::iterator it = p_pWege.begin(); it != p_pWege.end(); it++)
		(*it)->vAbfertigung();
}

void Kreuzung::vZeichnen()
{
	for (list<Weg*>::iterator it = p_pWege.begin(); it != p_pWege.end(); it++)
		(*it)->vZeichnen();
}

ostream& Kreuzung::ostreamAusgabe(ostream& os) const
{
	AktivesVO::ostreamAusgabe(os);
	os << "( ";
	for (list<Weg*>::const_iterator it = p_pWege.begin(); it != p_pWege.end(); it++)
		os << (*it)->getName() << " ";
	os << ")";
	return os;
}

istream& Kreuzung::istreamEingabe(istream& is)
{
	AktivesVO::istreamEingabe(is);
	is >> p_dTankstelle;
	return is;
}

Weg* Kreuzung::pZufaelligerWeg(Weg* pWeg)
{
	if (p_pWege.size() == 1)
		return p_pWege.front();
	list<Weg*>::iterator it = p_pWege.begin();
	for(unsigned int i = 0; i < rand() % (p_pWege.size()-1); i++) {
		it++;
	}
	if (*it == pWeg) {
		if (it != p_pWege.end())
			it++;
		else
			it--;
	}
	return *it;
}