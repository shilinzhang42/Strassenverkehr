#include "FzgFahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"
#include <algorithm>

FzgFahren::~FzgFahren()
{
}

double FzgFahren::dStrecke(Fahrzeug* pFzg, double dZeit)
{
	double dStrecke = pFzg->dGeschwindigkeit() * dZeit;
	double dUebrig = p_pWeg->getSchranke() - pFzg->getAbschnittStrecke();
	if (dUebrig == 0 && p_pWeg->getLaenge() == pFzg->getAbschnittStrecke()) //check with delta?!, && noetig?
		throw new Streckenende(pFzg, p_pWeg);
	dStrecke = min(dStrecke, dUebrig);
	return dStrecke;
}