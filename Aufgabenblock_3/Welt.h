#pragma once
#include <iostream>
#include <list>

using namespace std;

class Kreuzung;

class Welt
{
public:
	Welt();
	~Welt();

	void vEinlesen(istream& is);
	void vEinlesenMitGrafik(istream& is);
	void vSimulation();
	void vZeichnen();

private:
	list<Kreuzung*> p_pKreuzungen;
};

