#include "Fahrrad.h"


Fahrrad::~Fahrrad(void)
{
}

double Fahrrad::dGeschwindigkeit() const
{
	//pro 20km um 10% abnehmen
	//minimal 12km/h
	double dGeschwindigkeit = p_dMaxGeschwindigkeit;
	/*
	double dStrecke = p_dGesamtStrecke;
	while (dStrecke >= 20.0 && dGeschwindigkeit >= 12.0)
	{
		//auf 12.0 wieder hochsetzen.
		dGeschwindigkeit *= 0.9;
		dStrecke -= 20;
	}*/
	dGeschwindigkeit *= pow(0.9, floor(p_dGesamtStrecke / 20));
	if(dGeschwindigkeit < 12.0) dGeschwindigkeit = 12.0;// falls dGeschwindigkeit durch die Schleife auf unter 12.0 fällt
	return dGeschwindigkeit;
}
