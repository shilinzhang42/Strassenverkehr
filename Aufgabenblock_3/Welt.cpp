#include "Welt.h"
#include "Kreuzung.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "SimuClient.h"


Welt::Welt()
{
}


Welt::~Welt()
{
	for (list<Kreuzung*>::iterator it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); it++)
		delete (*it);
	vBeendeGrafik();
}

void Welt::vEinlesen(istream& is)
{
	int zeile = 1;
	string typ;
	try{
		while (!is.eof()){
			is >> typ;
			if (typ == "KREUZUNG"){
				Kreuzung* krz = new Kreuzung;
				is >> (*krz);
				p_pKreuzungen.push_back(krz);
			}
			else if (typ == "PKW") {
				PKW* pkw = new PKW;
				string nameS;
				double start;
				is >> (*pkw) >> nameS >> start;
				Kreuzung* kr = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameS));
				if (!kr)
					throw "'" + nameS + "' ist keine Kreuzung.";
				kr->vAnnahme(pkw, start);
			}
			else if (typ == "FAHRRAD") {
				Fahrrad* fahrrad = new Fahrrad;
				string nameS;
				double start;
				is >> (*fahrrad) >> nameS >> start;
				Kreuzung* kr = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameS));
				if (!kr)
					throw "'" + nameS + "' ist keine Kreuzung.";
				kr->vAnnahme(fahrrad, start);
			}
			else if (typ == "STRASSE") {
				string nameQ, nameZ, nameW1, nameW2;
				double laenge;
				int geschw;
				int ueberholverbot; //ignoriert fehler in z.15
				is >> nameQ >> nameZ >> nameW1 >> nameW2 >> laenge >> geschw >> ueberholverbot;
				if (geschw < 1 || geschw > 3)
					throw string("Geschwindigkeit ausserhalb der Grenzen.");
				if (ueberholverbot & 0xFFFFFE)
					cout << "Warnung in Zeile " + to_string(zeile) + ": Ueberholverbot ist kein bool: " << ueberholverbot << endl;
				Kreuzung* quelle = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameQ));
				Kreuzung* ziel = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameZ));
				if (!quelle)
					throw "'" + nameQ + "' ist keine Kreuzung.";
				if (!ziel)
					throw "'" + nameZ + "' ist keine Kreuzung.";
				quelle->vVerbinde(nameW1, nameW2, laenge, ziel, (Weg::Begrenzung)(geschw-1), ueberholverbot);
			}
			else
				cout << "Warnung in Zeile " + to_string(zeile) + ": unbekannter typ '" << typ << "'\n";
			zeile++;
		}
	}
	catch (string& str){
		throw "Zeile " + to_string(zeile) + ": " + str;
	}
}

void Welt::vEinlesenMitGrafik(istream& is)
{
	bInitialisiereGrafik(1000, 1000);
	int zeile = 1;
	string typ;
	try{
		while (!is.eof()){
			is >> typ;
			if (typ == "KREUZUNG"){
				Kreuzung* krz = new Kreuzung;
				int x, y;
				is >> (*krz) >> x >> y;
				p_pKreuzungen.push_back(krz);
				bZeichneKreuzung(x, y);
			}
			else if (typ == "PKW") {
				PKW* pkw = new PKW;
				string nameS;
				double start;
				is >> (*pkw) >> nameS >> start;
				Kreuzung* kr = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameS));
				if (!kr)
					throw "'" + nameS + "' ist keine Kreuzung.";
				kr->vAnnahme(pkw, start);
			}
			else if (typ == "FAHRRAD") {
				Fahrrad* fahrrad = new Fahrrad;
				string nameS;
				double start;
				is >> (*fahrrad) >> nameS >> start;
				Kreuzung* kr = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameS));
				if (!kr)
					throw "'" + nameS + "' ist keine Kreuzung.";
				kr->vAnnahme(fahrrad, start);
			}
			else if (typ == "STRASSE") {
				string nameQ, nameZ, nameW1, nameW2;
				int laenge;
				int geschw;
				int ueberholverbot; //ignoriert fehler in z.15
				int vertCount;
				is >> nameQ >> nameZ >> nameW1 >> nameW2 >> laenge >> geschw >> ueberholverbot >> vertCount;
				int* verts = new int[vertCount * 2];
				for (int i = 0; i < vertCount * 2; i++)
					is >> verts[i];

				Kreuzung* quelle = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameQ));
				Kreuzung* ziel = dynamic_cast<Kreuzung*>(AktivesVO::ptObjekt(nameZ));
				if (!quelle)
					throw "'" + nameQ + "' ist keine Kreuzung.";
				if (!ziel)
					throw "'" + nameZ + "' ist keine Kreuzung.";
				quelle->vVerbinde(nameW1, nameW2, laenge, ziel, (Weg::Begrenzung)geschw, ueberholverbot);

				bZeichneStrasse(nameW1.c_str(), nameW2.c_str(), laenge, vertCount, verts);

				delete[] verts;
			}
			else
				cout << "Warnung: unbekannter typ '" << typ << "'\n";
			zeile++;
		}
	}
	catch (string& str){
		throw str + " zeile " + to_string(zeile);
	}
}

void Welt::vSimulation()
{
	for (list<Kreuzung*>::iterator it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); it++) {
		(*it)->vAbfertigung();
	}
}

void Welt::vZeichnen()
{
	for (list<Kreuzung*>::iterator it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); it++) {
		(*it)->vZeichnen();
	}
}