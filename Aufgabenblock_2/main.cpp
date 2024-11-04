#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double dGlobaleZeit = 0.0;

void vFahrzeugHeader()
{
	cout << resetiosflags(ios::right) << setiosflags(ios::left);
	cout << setw(4) << "ID";
	cout << setw(7) << "Name" << " : ";
	cout << setw(10) << "KmH";
	cout << setw(10) << "MaxKmh";
	cout << setw(10) << "Abschnitt";
	cout << setw(10) << "Gesamt";
	cout << setw(7) << "Tank";
	cout << setw(10) << "Verbrauch";
	cout << "\n+++++++++++++++++++++++++++++++++++++++++" << endl;
}
/*Erstellen von Fahrzeugen, f0, f1 statisch und f2, f3, f4, f5 dynamisch;
**Ausgabe der Fahrzeuge mit ID, Name, Geschwindigkeit, MaxGeschwindigket, Gesamtstrecke;
*/
void vAufgabe_1()
{
	Fahrzeug f0, f1("F1");
	Fahrzeug *f2, *f3, *f4, *f5;
	f2 = new Fahrzeug;

	string sName;
	cout << "Name fuer f3? ";
	//cout.flush();
	cin >> sName; 

	f3 = new Fahrzeug(sName, 70.0); //sName wird als Name von f3 wegen der Eingabe übernommen
	f4 = new Fahrzeug("", 30.0);
	f5 = new Fahrzeug("", 30.0);

	vFahrzeugHeader();
	f0.vAusgabe(); cout << endl;
	f1.vAusgabe(); cout << endl;
	f2->vAusgabe(); cout << endl;
	f3->vAusgabe(); cout << endl;
	f4->vAusgabe(); cout << endl;
	f5->vAusgabe(); cout << endl;

	double dInterval = 0.3; //pro Schleifenlauf wird Abfertigung für jedes Fahrzeug aufgerufen, anschließend ausgegeben; 25 Mal
	for (int i = 0; i < 25; i++) {
		dGlobaleZeit += dInterval;
		f0.vAbfertigung();
		f1.vAbfertigung();
		f2->vAbfertigung();
		f3->vAbfertigung();
		f4->vAbfertigung();
		f5->vAbfertigung();
		f5->vAbfertigung();

		cout << endl;
		f0.vAusgabe(); cout << endl;
		f1.vAusgabe(); cout << endl;
		f2->vAusgabe(); cout << endl;
		f3->vAusgabe(); cout << endl;
		f4->vAusgabe(); cout << endl;
		f5->vAusgabe(); cout << endl;
	}
	/*löschen des Heaps*/
	delete f5;
	delete f4;
	delete f3;
	delete f2;
}

void vAufgabe_1_deb()
{
	Fahrzeug f0, f1, f2, f3;
	Fahrzeug* pFahrzeuge[4] = { &f0, &f1, &f2, &f3 };

	vFahrzeugHeader();
	for (int i = 0; i < 4; i++)
	{
		pFahrzeuge[i]->vAusgabe(); cout << endl;
	}

	pFahrzeuge[2] = 0; //Fehler einbauen: Fahrzeug - Pointer pFahrzeuge[2] zeigt auf NULL

	for (int i = 0; i < 4; i++) {
		pFahrzeuge[i]->vAusgabe(); cout << endl; //Fehler bei f2: Weil pFahrzeuge[2] auf NULL zeigt, und nicht auf f2, kann f2->Ausgabe() aufgerufen werden;
	}
}
/*Erstellen von Fahrrädern und PKWs, die von Fahrzeug erben; dabei gibt der Benutzer die Anzahl der Fahrräder und PKWs an*/
void vAufgabe_2()
{
	int iPKWs, iFahrraeder;
	cout << "Anzahl PKWs? ";
	cin >> iPKWs;
	cout << "Anzahl Fahrraeder? ";
	cin >> iFahrraeder;

	vector<Fahrzeug*> fahrzeuge; //Die Fahrzeuge werden in einen Vektor eingetragen.
	for (int i = 0; i < iPKWs; i++) {
		string sName;
		double dMaxGeschwindigkeit, dVerbrauch;
		cout << "Fahrzeug " << i << endl;
		cout << "Name: "; cin >> sName;
		cout << "Max Geschwindigkeit: "; cin >> dMaxGeschwindigkeit;
		cout << "Verbrauch: "; cin >> dVerbrauch;
		cout << endl;
		PKW* pkw = new PKW(sName, dMaxGeschwindigkeit, dVerbrauch); //PKW* pkw zeigt immer auf den neuen PKW-Objekt

		fahrzeuge.push_back(pkw);
	}

	for (int i = 0; i < iFahrraeder; i++) {
		cout << "Fahrrad" << "Nr. " << i << endl;
		string sName;
		double dMaxGeschwindigkeit;
		cout << "Fahrzeug " << i+iPKWs << endl;
		cout << "Name: "; cin >> sName;
		cout << "Max Geschwindigkeit: "; cin >> dMaxGeschwindigkeit;
		cout << endl;
		Fahrrad* fahrrad = new Fahrrad(sName, dMaxGeschwindigkeit);

		fahrzeuge.push_back(fahrrad);
	}

	vFahrzeugHeader();
	double dInterval = 0.1;
	while (dGlobaleZeit < 5.0)
	{
		dGlobaleZeit += dInterval;//dGlobaleZeit anfangs 0;
		for (vector<Fahrzeug*>::iterator it = fahrzeuge.begin(); it != fahrzeuge.end(); it++) {
			(*it)->vAbfertigung();
			if (fabs(dGlobaleZeit - 3.0) < 0.0000000001) //if (dGlobaleZeit == 3.0) Tanke voll auf 55. 
				(*it)->dTanken();
			(*it)->vAusgabe(); cout << endl;
		}
		cout << "----" << endl;
	}

	for (vector<Fahrzeug*>::iterator it = fahrzeuge.begin(); it != fahrzeuge.end(); it++) {
		delete *it;
	}
}

void vAufgabe_3()
{
	vFahrzeugHeader();
	dGlobaleZeit = 1.0;
	PKW p0("test", 10.0, 100, 3000), p1("test2", 20.0);
	p1.vAbfertigung();
	cout << p0 << endl << p1 << endl;
	cout << "test < test2? " << (p0 < p1) << endl;

	/*Benutze copy-Constructor, übernimmt Verbrauch und Tankvolumen von p0, */
	PKW copy(p1);
	cout << "Kopie:\n" << copy << endl;
	/*Benutze diesmal Zuweisungsoperator, übernimmt alle Attribute, z.B. auch p_iID aus Fahrzeug von p0*/
	PKW assign;
	assign = p1;
	cout << "Zuweisung:\n" << assign << endl;
}

void vAufgabe_4()
{
	vFahrzeugHeader();
	PKW p0("auto", 100, 100);
	Fahrrad f0("bmx", 60);

	Weg weg("weg", 100, Weg::Innerorts);
	weg.vAnnahme(&p0, 3.0);
	weg.vAnnahme(&f0);
	cout << weg << endl;

	double dInterval = 0.3;
	while (dGlobaleZeit < 6.0)
	{
		dGlobaleZeit += dInterval;//dGlobaleZeit anfangs 0;
		weg.vAbfertigung();
		cout << p0 << endl;
		cout << f0 << endl;
	}
}

void vAufgabe_5()
{
	int pPoints[4] = { 100, 250, 600, 250 };

	bInitialisiereGrafik(800, 500);
	PKW p0("auto", 200, 100);
	Fahrrad f0("bmx", 60);

	Weg weg1("weg1", 500, Weg::Landstrasse);
	Weg weg2("weg2", 500, Weg::Landstrasse);

	bZeichneStrasse(weg1.getName().c_str(), weg2.getName().c_str(), 500, 2, pPoints);

	weg1.vAnnahme(&p0, 3.0);
	weg2.vAnnahme(&f0);

	double dInterval = 0.3;
	while (dGlobaleZeit < 10.0)
	{
		dGlobaleZeit += dInterval;//dGlobaleZeit anfangs 0;
		vSetzeZeit(dGlobaleZeit);
		weg1.vAbfertigung();
		weg2.vAbfertigung();
		p0.vZeichnen(&weg1);
		f0.vZeichnen(&weg2);
	}

	vBeendeGrafik();
}

void vAufgabe_6a()
{
	LazyListe<int> liste;
	for (int i = 0; i < 10; i++)
		liste.push_back(rand() % 10 + 1);
	liste.vAktualisieren();

	for (LazyListe<int>::iterator it = liste.begin(); it != liste.end(); it++) {
		cout << *it << endl;
		if (*it > 5)
			liste.erase(it);
	}

	cout << "===" << endl;

	for (LazyListe<int>::iterator it = liste.begin(); it != liste.end(); it++) {
		cout << *it << endl;
	}

	cout << "===" << endl;

	liste.vAktualisieren();
	for (LazyListe<int>::iterator it = liste.begin(); it != liste.end(); it++) {
		cout << *it << endl;
	}

	cout << "===" << endl;

	liste.push_front(-1);
	liste.push_back(99);

	for (LazyListe<int>::const_iterator it = liste.begin(); it != liste.end(); it++) {
		cout << *it << endl;
	}

	cout << "===" << endl;

	liste.vAktualisieren();
	for (LazyListe<int>::iterator it = liste.begin(); it != liste.end(); it++) {
		cout << *it << endl;
	}
}

void main() {
	vAufgabe_5();

	/*string tmp;
	cin >> tmp;*/
	system("pause");
}