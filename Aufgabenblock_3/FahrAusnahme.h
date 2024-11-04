#pragma once

class Fahrzeug;
class Weg;

class FahrAusnahme
{
public:
	FahrAusnahme(Fahrzeug* pFzg, Weg* pWeg);
	virtual ~FahrAusnahme();
	virtual void vBearbeiten() = 0;
protected:
	Fahrzeug* p_pFahrzeug;
	Weg* p_pWeg;
};

