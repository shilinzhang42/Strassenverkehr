#pragma once
#include "FahrAusnahme.h"

class Streckenende :
	public FahrAusnahme
{
public:
	Streckenende(Fahrzeug* pFzg, Weg* pWeg);
	virtual ~Streckenende();
	virtual void vBearbeiten();
};

