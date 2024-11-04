#include "FahrAusnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"

FahrAusnahme::FahrAusnahme(Fahrzeug* pFzg, Weg* pWeg) : p_pFahrzeug(pFzg), p_pWeg(pWeg)
{
}


FahrAusnahme::~FahrAusnahme()
{
}
