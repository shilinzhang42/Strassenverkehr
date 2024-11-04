#pragma once
#include <string>

using namespace std;

class Fahrzeug
{
public:
	Fahrzeug();
	Fahrzeug(const Fahrzeug& other);
	Fahrzeug(const string& sName);
	Fahrzeug(const string& sName, const double dMaxGeschwindigkeit);
	virtual ~Fahrzeug();

	virtual void vAbfertigung();
	void vAusgabe() const;
	virtual double dGeschwindigkeit() const;

	virtual double dTanken(double dMenge = -1.0);

	virtual ostream& ostreamAusgabe(ostream& os) const;

	bool operator<(const Fahrzeug& other) const; //innerhalb der Klasse: linker Operand = this Zeiger , Rechter Operand = Parameter
	
	Fahrzeug& operator=(const Fahrzeug& other);
private:
	string p_sName;
	int p_iID;

	double p_dGesamtZeit;

	static int p_iMaxID;

	void vInitialisiere();

protected:
	double p_dGesamtStrecke, p_dMaxGeschwindigkeit, p_dZeit;
};

ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug); //außerhalb der Klasse: linker Operand = erster Paramenter , Rechter Operand = zweiter Parameter