#pragma once
#include <string>

using namespace std;

class AktivesVO
{
public:
	AktivesVO();
	AktivesVO(const AktivesVO& other);
	AktivesVO(const string& sName);
	virtual ~AktivesVO();

	virtual ostream& ostreamAusgabe(ostream& os) const;
	void vAusgabe() const;

	virtual void vAbfertigung() = 0;


	AktivesVO& operator=(const AktivesVO& other);

	const string& getName() const;

private:
	string p_sName;
	int p_iID;

	static int p_iMaxID;

	void vInitialisiere();
protected:
	double p_dZeit;
};


ostream& operator<<(ostream& os, const AktivesVO& vo); //außerhalb der Klasse: linker Operand = erster Paramenter , Rechter Operand = zweiter Parameter