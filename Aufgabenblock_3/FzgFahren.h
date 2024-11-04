#pragma once
#include "FzgVerhalten.h"

class FzgFahren : public FzgVerhalten
{
public:
	FzgFahren(Weg* pWeg) : FzgVerhalten(pWeg) {}
	virtual ~FzgFahren();

	virtual double dStrecke(Fahrzeug* pFzg, double dZeit);
};

