#pragma once
#include "FahrAusnahme.h"

class Losfahren :
	public FahrAusnahme
{
public:
	Losfahren(Fahrzeug* pFzg, Weg* pWeg);
	virtual ~Losfahren();
	virtual void vBearbeiten();
};

