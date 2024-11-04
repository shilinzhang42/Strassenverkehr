#pragma once

class Weg;
class Fahrzeug;

class FzgVerhalten
{
public:
	FzgVerhalten(Weg* pWeg);
	virtual ~FzgVerhalten();

	virtual double dStrecke(Fahrzeug* pFzg, double dZeit) = 0;

	Weg* getWeg() const;

protected:
	Weg* p_pWeg;
};

