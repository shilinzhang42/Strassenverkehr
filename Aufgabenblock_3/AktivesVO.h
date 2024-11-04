#pragma once
#include <string>
#include <map>

using namespace std;

class AktivesVO
{
public:
	AktivesVO();
	AktivesVO(const AktivesVO& other);
	AktivesVO(const string& sName);
	virtual ~AktivesVO();

	virtual ostream& ostreamAusgabe(ostream& os) const;
	virtual istream& istreamEingabe(istream& is);
	void vAusgabe() const;

	virtual void vAbfertigung() = 0;


	AktivesVO& operator=(const AktivesVO& other);

	const string& getName() const;
	static AktivesVO* ptObjekt(string pName);

private:
	string p_sName;
	int p_iID;

	static int p_iMaxID;
	static map<string, AktivesVO*> p_pVOs;

	void vInitialisiere();
protected:
	double p_dZeit;
};


ostream& operator<<(ostream& os, const AktivesVO& vo); //auﬂerhalb der Klasse: linker Operand = erster Paramenter , Rechter Operand = zweiter Parameter
istream& operator>>(istream& is, AktivesVO& vo); //auﬂerhalb der Klasse: linker Operand = erster Paramenter , Rechter Operand = zweiter Parameter