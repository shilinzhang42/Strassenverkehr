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
	if (p_pWeg) {
		double dUebrig = p_pWeg->getLaenge() - pFzg->getAbschnittStrecke();
		if (dUebrig == 0) //check with delta?!
			throw new Streckenende(pFzg, p_pWeg);
		dStrecke = min(dStrecke, dUebrig);
	}
	return dStrecke;
}