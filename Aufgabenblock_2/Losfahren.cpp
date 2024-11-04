#include "Losfahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>

using namespace std;

Losfahren::Losfahren(Fahrzeug* pFzg, Weg* pWeg) : FahrAusnahme(pFzg, pWeg)
{
}


Losfahren::~Losfahren()
{
}


void Losfahren::vBearbeiten()
{
	cout << ">>> Losfahren: " << p_pFahrzeug->getName() << " auf " << p_pWeg->getName() << endl;
	p_pWeg->vAbgabe(p_pFahrzeug);
	p_pWeg->vAnnahme(p_pFahrzeug);
}
