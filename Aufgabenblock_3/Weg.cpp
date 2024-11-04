#include "Weg.h"
#include "Fahrzeug.h"
#include "FahrAusnahme.h"
#include <iomanip>

Weg::Weg() : AktivesVO()
{
	p_dLaenge = 0.0;
}


Weg::Weg(const string& sName, double dLaenge, Weg::Begrenzung eLimit, bool bUeberholverbot) : AktivesVO(sName)
{
	p_dLaenge = dLaenge;
	p_eLimit = eLimit;
	p_bUeberholverbot = bUeberholverbot;
}

Weg::~Weg()
{
}

void Weg::vAbfertigung()
{
	p_dSchranke = p_dLaenge;
	for (list<Fahrzeug*>::const_iterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		try {
			(*it)->vAbfertigung();
		} catch (FahrAusnahme* ex) {
			ex->vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

void Weg::vAnnahme(Fahrzeug* pFzg)
{
	p_pFahrzeuge.push_back(pFzg);
	pFzg->vNeueStrecke(this);
}

void Weg::vAnnahme(Fahrzeug* pFzg, double dStartzeit)
{
	p_pFahrzeuge.push_front(pFzg);
	pFzg->vNeueStrecke(this, dStartzeit);
}

void Weg::vAbgabe(Fahrzeug* pFzg)
{
	for (LazyListe<Fahrzeug*>::iterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		if (*it == pFzg) {
			p_pFahrzeuge.erase(it);
			return;
		}
	}
}

ostream& Weg::ostreamAusgabe(ostream& os) const
{
	AktivesVO::ostreamAusgabe(os);
	os << setw(10) << p_dLaenge;

	os << "( ";
	for (list<Fahrzeug*>::const_iterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		os << (*it)->getName() << " ";
	}
	os << ")";

	return os;
}

Weg::Begrenzung Weg::getLimit() const
{
	return p_eLimit;
}

double Weg::getSchranke() const
{
	return p_dSchranke;
}

void Weg::setSchranke(double dSchranke)
{
	if (p_bUeberholverbot)
		p_dSchranke = dSchranke;
}

void Weg::vZeichnen()
{
	for (list<Fahrzeug*>::const_iterator it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
		(*it)->vZeichnen(this);
}

void Weg::setRueck(Weg* pRueck)
{
	p_pRueck = pRueck;
}

Weg* Weg::getRueck()
{
	return p_pRueck;
}

void Weg::setZiel(Kreuzung* pZiel)
{
	p_pZielKreuzung = pZiel;
}

Kreuzung* Weg::getZiel()
{
	return p_pZielKreuzung;
}