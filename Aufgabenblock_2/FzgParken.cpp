#include "FzgParken.h"
#include <stdlib.h> //exit
#include "Losfahren.h"

FzgParken::~FzgParken()
{
}


double FzgParken::dStrecke(Fahrzeug* pFzg, double dZeit)
{
	if ((p_dStartzeit -= dZeit) <= 0.000000000000001)
		throw new Losfahren(pFzg, p_pWeg);
	return 0.0;
}