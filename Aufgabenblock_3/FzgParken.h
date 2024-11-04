#pragma once
#include "FzgVerhalten.h"

class FzgParken : public FzgVerhalten
{
public:
	FzgParken(Weg* pWeg, double dStartzeit) : FzgVerhalten(pWeg), p_dStartzeit(dStartzeit) {}
	virtual ~FzgParken();
	
	virtual double dStrecke(Fahrzeug* pFzg, double dZeit);

private:
	double p_dStartzeit;
};

